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

void SshConnection::setHost(QString host)
{
    host_ = host;
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

void SshConnectionModel::setHost(int index, QString value)
{
    if (index < 0 || index >= connections.count())
        return;

    connections[index].setHost(value);
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

Qt::ItemFlags SshConnectionModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool SshConnectionModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug() << "setData" << index << " " << role;
    if (index.isValid() && role == Qt::EditRole) {

        qDebug() << 234;
        emit dataChanged(index, index);

        return true;
    }
    return false;
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
