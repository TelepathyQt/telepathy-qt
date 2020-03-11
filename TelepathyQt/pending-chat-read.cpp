/**
 * This file is part of TelepathyQt
 *
 * @copyright Copyright (C) 2020 Alexander Akulich <akulichalexander@gmail.com>
 * @license LGPL 2.1
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "TelepathyQt/pending-chat-read.h"

#include "TelepathyQt/_gen/pending-chat-read.moc.hpp"

#include "TelepathyQt/debug-internal.h"

#include <TelepathyQt/Connection>
#include <TelepathyQt/Constants>

#include <QDBusPendingCallWatcher>

namespace Tp
{

struct TP_QT_NO_EXPORT PendingChatReadOperation::Private
{
    QVariantMap request;
    QString messageToken;
    ConnectionPtr connection;
};

/**
 * \class PendingChatReadOperation
 * \ingroup clientchannel
 * \headerfile TelepathyQt/pending-channel.h <TelepathyQt/PendingChatReadOperation>
 *
 * \brief The PendingChatReadOperation class represents the parameters of and the reply to
 * an asynchronous channel request.
 *
 * Instances of this class cannot be constructed directly; the only way to get
 * one is trough Connection.
 *
 * See \ref async_model
 */

/**
 * Construct a new PendingChatReadOperation object.
 *
 * \param connection Connection to use.
 * \param request A dictionary containing the desirable properties.
 * \param create Whether createChannel or ensureChannel should be called.
 */

PendingChatReadOperation::PendingChatReadOperation(const ConnectionPtr &connection,
        const QVariantMap &request, const QString &messageToken)
    : PendingOperation(connection),
      mPriv(new Private)
{
    mPriv->request = request;
    mPriv->messageToken = messageToken;
    mPriv->connection = connection;

    if (connection.isNull()) {
        warning() << "ChatRead: No connection provided";
        setFinishedWithError(TP_QT_ERROR_NOT_AVAILABLE,
                             QLatin1String("Unable to get connection to mark Chat Read"));
        return;
    }

    Client::ConnectionInterfaceChatReadInterface *chatReadInterface =
        mPriv->connection->interface<Client::ConnectionInterfaceChatReadInterface>();

    if (!chatReadInterface) {
        warning() << "ChatRead: Connection interface is not available";
        setFinishedWithError(TP_QT_ERROR_NOT_AVAILABLE,
                             QLatin1String("Unable to get ChatRead interface"));
        return;
    }

    QDBusPendingCallWatcher *watcher =
            new QDBusPendingCallWatcher(chatReadInterface->MarkRead(mPriv->request, mPriv->messageToken));
    connect(watcher, &QDBusPendingCallWatcher::finished, this, &PendingChatReadOperation::onMarkReadFinished);
}

/**
 * Class destructor.
 */
PendingChatReadOperation::~PendingChatReadOperation()
{
    delete mPriv;
}

/**
 * Return the connection through which the channel request was made.
 *
 * Note that if this channel request was created through Account, a null ConnectionPtr will be
 * returned.
 *
 * \return A pointer to the Connection object.
 */
ConnectionPtr PendingChatReadOperation::connection() const
{
    return mPriv->connection;
}

void PendingChatReadOperation::onMarkReadFinished(QDBusPendingCallWatcher *watcher)
{
    if (watcher->isError()) {
        setFinishedWithError(watcher->error());
    } else {
        setFinished();
    }

    watcher->deleteLater();
}

} // Tp