#include "ydapi.h"

#include <QNetworkRequest>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QFile>
#include <QFileInfo>

#define NAMOR_API_CONNECT_REPLY_FINISHED(x)    connect(m_reply, SIGNAL(finished()), SLOT(x()))

YDAPI::YDAPI(QObject *parent) : QObject(parent)
{
    m_manager = new QNetworkAccessManager(this);
}

void YDAPI::setToken(QString token)
{
    m_token = token;
}

void YDAPI::createFolder(QString folderName)
{
    this->m_folderName = folderName;

    QString url = "https://cloud-api.yandex.net:443/v1/disk/resources?path=app:/";
    url.append(m_folderName);

    //QNetworkRequest request = createRequest(url);

    if(startRequest(createRequest(url), nPUT)) {
        connect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(emitFolderCreated()));
    }
}

void YDAPI::upload(QString fileName)
{
    m_fileNameWithPath 		= fileName;
    m_fileNameWithoutPath 	= QFileInfo(m_fileNameWithPath).fileName();

    QString url = "https://cloud-api.yandex.net:443/v1/disk/resources/upload?overwrite=true&path=app:/";
    url.append(m_folderName + "/");
    url.append(m_fileNameWithoutPath);

    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setRawHeader(QByteArray("Accept"), QByteArray("application/json"));
    request.setRawHeader(QByteArray("Authorization"), QByteArray(m_token.toUtf8()));

    if(startRequest(request, nGET)) {
        connect(m_reply, SIGNAL(finished()), SLOT(uploadFilePUT()));
    }
}

void YDAPI::uploadFilePUT()
{
    QNetworkReply *reply = m_reply;

    QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsonObj = jsonDoc.object();

    QString href = jsonObj["href"].toString();          //PUT upload url
    if(href.isEmpty()){
        QString errorMsg = jsonObj.value("error").toString() + ": " + jsonObj.value("message").toString();
        emit onError(1, errorMsg);
        return;
    }

    QFile *file = new QFile(m_fileNameWithPath);
    if(!file->open(QIODevice::ReadOnly)){
        qDebug() << "Dont read";
        return;
    }

    QNetworkRequest request;
    request.setUrl(QUrl(href));
    request.setRawHeader(QByteArray("Accept"), 		  QByteArray("application/json"));
    request.setRawHeader(QByteArray("Authorization"), QByteArray(m_token.toUtf8()));

    if(startRequest(request, nPUT, "", file)){
        //connect(m_reply, SIGNAL(uploadProgress(qint64,qint64)),
        //        this, 	 SIGNAL(uploadProgress(qint64,qint64)));

        connect(m_reply, SIGNAL(finished()), this, SLOT(onUploadFilePUT()));
    }
}

void YDAPI::onUploadFilePUT()
{
    QNetworkReply *reply = m_reply;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsonObj = jsonDoc.object();

    if(jsonObj.find("error") != jsonObj.end()){
        emit onError(1, jsonObj.value("message").toString());
        return;
    }
    emit finished(0, "File uploaded");
}

void YDAPI::onSslErrors(QList<QSslError> errors)
{
    QString message;
    for (int i = 0; i < errors.count(); i++)
        message += errors[i].errorString() + "\n";

    emit onError(1, message);
}

void YDAPI::onNetworkError(QNetworkReply::NetworkError error)
{
    emit onError(error, m_reply->errorString());
}

void YDAPI::emitFolderCreated()
{
    disconnect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(emitFolderCreated()));

    emit finished(0, "Folder created");
}

void YDAPI::emitFileUploaded()
{
    emit finished(0, "File uploaded");
}

QNetworkRequest YDAPI::createRequest(QString url)
{
    QNetworkRequest request;

    request.setUrl(QUrl(url));
    request.setRawHeader(QByteArray("Accept"), QByteArray("application/json"));
    request.setRawHeader(QByteArray("Authorization"), QByteArray(m_token.toUtf8()));

    return request;
}

bool YDAPI::startRequest(const QNetworkRequest &request,
                         YDAPI::RequestMethod method,
                         const QString &data, QIODevice *io)
{
    QNetworkReply *reply;

    switch (method) {
    case nGET:
        reply = m_manager->get(request);
        break;

    case nPOST:
        if(io != NULL) {
            reply = m_manager->post(request, io);
        } else {
            reply = m_manager->post(request, data.toUtf8());
        }
        break;

     case nPUT:
        if(io != NULL) {
            reply = m_manager->put(request, io);
        } else {
            reply = m_manager->put(request, data.toUtf8());
        }
        break;

    case nDELETE:
        reply = m_manager->deleteResource(request);
        break;

    default:
        return setLastError(1, "Not implemented");
    }

    m_reply = reply;

    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this,    SLOT(onNetworkError(QNetworkReply::NetworkError)));

    connect(m_reply, SIGNAL(sslErrors(QList<QSslError>)),
            this, 	 SLOT(onSslErrors(QList<QSslError>)));

    if(method == nPUT || method == nPOST) {
        connect(m_reply, SIGNAL(uploadProgress(qint64,qint64)),
                this,	 SIGNAL(uploadProgress(qint64,qint64)));
    }

    return true;
}

bool YDAPI::setLastError(int code, const QString message)
{
    emit onError(code, message);
    return code == 0;
}
