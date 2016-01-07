#include "sshconnectionmodel.h"

#include <QDebug>

SshConnection::SshConnection(const QString &name, const QString &host)
    : name_(name), host_(host)
{
}

QString SshConnection::name() const
{
    return name_;
}

QString SshConnection::host() const
{
    return host_;
}

SshConnectionModel::SshConnectionModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void SshConnectionModel::addSshConnection(const SshConnection &connection)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    connections << connection;
    endInsertRows();
}

void SshConnectionModel::removeRows(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    connections.removeAt(index);
    endRemoveRows();
}

int SshConnectionModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return connections.count();
}

QVariant SshConnectionModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= connections.count())
        return QVariant();

    const SshConnection &connection = connections[index.row()];
    if (role == NameRole)
        return connection.name();
    else if (role == HostRole)
        return connection.host();
    return QVariant();
}

QList<SshConnection> SshConnectionModel::getConnections() const
{
    return connections;
}

QHash<int, QByteArray> SshConnectionModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[HostRole] = "host";
    return roles;
}

QDataStream &operator<<(QDataStream &out, const SshConnectionModel &sshConnectionModel)
{
    for (auto &it : sshConnectionModel.getConnections())
        out << it.name() << it.host();
    return out;
}


QDataStream &operator>>(QDataStream &in, SshConnectionModel &sshConnectionModel)
{
    QString name;
    QString host;

    while(true){
        in >> name >> host;
        if (in.status() != in.Ok)
            break;

        sshConnectionModel.addSshConnection(SshConnection(name, host));
    }

    return in;
}
