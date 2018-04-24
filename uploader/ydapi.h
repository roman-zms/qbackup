#ifndef YDAPI_H
#define YDAPI_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>

class YDAPI : public QObject
{
    Q_OBJECT
public:
    explicit YDAPI(QObject *parent = nullptr);

public slots:
    //param: token - oauth token
    void setToken(QString token);

    //param: folderName - folder name to create
    void createFolder(QString folderName);

    //param: fileName - file to upload
    void upload(QString fileName);

    void uploadToFolder(QString fileName, QString folderName);

signals:
    void finished(int code, QString info);	//new
    void onError(int code, QString errorMessage);			//new

    void uploadFinished();

    void uploadProgress(qint64 sent, qint64 total);		//emit upload progress

private slots:
    void uploadFilePUT();
    void onUploadFilePUT();

    void onSslErrors(QList<QSslError> errors);
    void onNetworkError(QNetworkReply::NetworkError error);

    void emitFolderCreated();
    void emitFileUploaded();

private:
    typedef enum {
        nGET,
        nPOST,
        nPUT,
        nDELETE
    } RequestMethod;

    QNetworkRequest createRequest(QString url);

    bool startRequest(const QNetworkRequest& request, RequestMethod method = nGET,
                      const QString& data = "", QIODevice* io = NULL, bool progress = false);

    bool setLastError(int code, const QString message ="");

    //--------------------variables

    int m_errorCode;					//operation code
    QString m_errorMessage;

    int m_retry;

    QString m_fileNameWithoutPath;		//File name without path
    QString m_fileNameWithPath;			//File name with absolute path
    QString m_folderName;			//Uploads folder name	(remove?)
    QString m_token;					//OAuth token

    QNetworkAccessManager *m_manager;
    QNetworkReply *m_reply;

    qint64 m_sent, m_total;				//Upload progress
};

#endif // YDAPI_H
