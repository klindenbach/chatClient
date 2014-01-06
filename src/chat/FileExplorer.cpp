#include <QFileInfo>
#include "chat/FileExplorer.hpp"

using namespace chat;

FileExplorer::FileExplorer(QString *root, QObject *parent) : QObject(parent) {
    this->rootPath = root;
    this->lastUsedPath = NULL;
    this->baseWidget = NULL;
}

FileExplorer::~FileExplorer() {
    if (this->rootPath != NULL) {
        delete this->rootPath;
    }
    freeBaseWidget();
}

QWidget *FileExplorer::getBaseWidget() const {
    return this->baseWidget;
}
void FileExplorer::setBaseWidget(QWidget *baseW) {
    // Will need to make an informed decision on whether to free old base widget
    this->baseWidget = baseW;
}

void FileExplorer::freeBaseWidget() {
    if (this->baseWidget != NULL) {
        delete this->baseWidget;
    }
}

void FileExplorer::setLastUsedPath(const QString newPath) {

    if (this->lastUsedPath != NULL) {
        delete this->lastUsedPath;
    }

    this->lastUsedPath = new QString(newPath);
}

QStringList FileExplorer::getMatchesViaDialog(const QString &srcPath, const QString &filter) {
  QStringList nameMatches = QFileDialog::getOpenFileNames(
      NULL, tr("Select files"), srcPath, filter
  );

  // Memorize as last used
  this->setLastUsedPath(srcPath);

  return nameMatches;
}

QFile *FileExplorer::openFileForUpload() {
  QString fileName = QFileDialog::getOpenFileName(
      this->baseWidget, tr("Select file"), QDir::currentPath()
  );

  if (! fileName.isEmpty()){
    QFile *file = new QFile(fileName);

    if (! file->exists()) {
      QMessageBox::information(
          this->baseWidget,tr("File explorer"), tr("Cannot load %1.").arg(fileName)
      );
      return NULL;
    }

    QFileInfo fInfo(*file);
    uint byteCount = file->bytesAvailable();

    if (! fInfo.isFile()) {
        QMessageBox::information(
           this->baseWidget, tr("Uploader"), tr("%1. is not a regular file").arg(fileName)
        );
    } else if (! file->isReadable()) {
        QMessageBox::information(
           this->baseWidget, tr("Uploader"), tr("No read permissions for %1.").arg(fileName)
        );
    } else if (! byteCount) {
        QMessageBox::information(
           this->baseWidget, tr("Uploader"), tr("Attempting to upload an empty file")
        );
    } else { // Good for return
        return file;
    }

    // By this point, release memory
    delete file;
  }

  return NULL;
}

