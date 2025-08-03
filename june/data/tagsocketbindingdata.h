#ifndef TAGSOCKETBINDINGDATA_H
#define TAGSOCKETBINDINGDATA_H

#include <vector>
#include <QObject>

#include <tagsystem/tagsocket.h>

class QNetworkAccessManager;
class QNetworkRequestFactory;

class TagSocketBinding
{
public:
    explicit TagSocketBinding(const QString& tagSocketSubsystem, const QString& tagSocketName, const QString& tag, TagSocket::Type type);

    const QString& tagSocketSubsystem() const { return tagSocketSubsystem_;}
    const QString& tagSocketName() const { return tagSocketName_;}
    const QString& tag() const{ return tag_;}
    TagSocket::Type type() const{ return type_;}

    void setTag(const QString& tag);
private:
    QString tagSocketSubsystem_;
    QString tagSocketName_;
    QString tag_;
    TagSocket::Type type_ = TagSocket::eNone;

};

class TagSocketBindingData : public QObject
{
    Q_OBJECT
public:
    explicit TagSocketBindingData(QNetworkAccessManager &nam, QNetworkRequestFactory &networkRequestFactory, QObject *parent = nullptr);

    const TagSocketBinding& binding(int index) const;
    int numberOfBindings() const;

    void updateTag(int index, const QString& tag);

    void fetchFromServer();
signals:
    void dataReady();
    void bindingUpdated(int index);

private slots:
    void onFetchFromServerFinnished();
    void onHookupOnServerFinnished();

private:
    QNetworkRequestFactory& networkRequestFactory_;
    QNetworkAccessManager& networkAccessManager_;

    std::vector<TagSocketBinding> tagSocketBindings_;
};

#endif // TAGSOCKETBINDINGDATA_H
