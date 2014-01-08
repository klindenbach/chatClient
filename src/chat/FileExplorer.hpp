#ifndef FILEEXPLORER_HPP
#define FILEEXPLORER_HPP

#include <QDir>
#include <QFile>
#include <QObject>
#include <QWidget>
#include <QFileDialog>
#include <QStringList>
#include <QMessageBox>
#include <QMainWindow>

namespace chat {

class FileExplorer : public QObject {

    public:
        FileExplorer(QString *root, QObject *parent=0);
        ~FileExplorer();
        void show();

        QWidget *getBaseWidget() const;
        inline void setBaseWidget(QWidget *baseW);
	inline void changeBaseWidgetOwnerShip(bool ownershipBool);

        void freeBaseWidget();

        QStringList getMatchesViaDialog(
	  const QString &srcPath, const QString &filter
	);

        QFile *openFileForUpload();

    private:
	bool ownsBaseWidget;
        QString *lastUsedPath;
        QString *rootPath;
        QWidget *baseWidget;

        inline void setLastUsedPath(const QString newPath);
};
}
#endif // FILEEXPLORER_HPP
