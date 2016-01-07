#ifndef SSHCONNECTIONMODEL_H
#define SSHCONNECTIONMODEL_H

#include <QAbstractListModel>

class SshConnection
{
public:
    SshConnection(const QString &name, const QString &host);

    QString name() const;
    QString host() const;

private:
    QString name_;
    QString host_;
};

class SshConnectionModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum SshConnectionRoles {
        NameRole = Qt::UserRole + 1,
        HostRole
    };

    SshConnectionModel(QObject *parent = 0);

    void addSshConnection(const SshConnection &connection);
    void removeRows(int index);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<SshConnection> connections;
};

#endif // SSHCONNECTIONMODEL_H
