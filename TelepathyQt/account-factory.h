/**
 * This file is part of TelepathyQt
 *
 * @copyright Copyright (C) 2010 Collabora Ltd. <http://www.collabora.co.uk/>
 * @copyright Copyright (C) 2010 Nokia Corporation
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

#ifndef _TelepathyQt_account_factory_h_HEADER_GUARD_
#define _TelepathyQt_account_factory_h_HEADER_GUARD_

#ifndef IN_TP_QT_HEADER
#error IN_TP_QT_HEADER
#endif

#include <TelepathyQt/Global>
#include <TelepathyQt/SharedPtr>
#include <TelepathyQt/Types>

#include <TelepathyQt/Account>
#include <TelepathyQt/Feature>
#include <TelepathyQt/FixedFeatureFactory>

class QDBusConnection;

namespace Tp
{

class PendingReady;

class TP_QT_EXPORT AccountFactory : public FixedFeatureFactory
{
    Q_OBJECT
    Q_DISABLE_COPY(AccountFactory)

public:
    static AccountFactoryPtr create(const QDBusConnection &bus,
            const Features &features = Features());

    ~AccountFactory() override;

    PendingReady *proxy(const QString &busName, const QString &objectPath,
            const ConnectionFactoryConstPtr &connFactory,
            const ChannelFactoryConstPtr &chanFactory,
            const ContactFactoryConstPtr &contactFactory) const;

protected:
    AccountFactory(const QDBusConnection &bus, const Features &features);

    virtual AccountPtr construct(const QString &busName, const QString &objectPath,
            const ConnectionFactoryConstPtr &connFactory,
            const ChannelFactoryConstPtr &chanFactory,
            const ContactFactoryConstPtr &contactFactory) const;
    QString finalBusNameFrom(const QString &uniqueOrWellKnown) const override;
    // Nothing we'd like to prepare()
    // Fixed features

private:
    struct Private;
    Private *mPriv; // Currently unused, just for future-proofing
};

} // Tp

#endif
