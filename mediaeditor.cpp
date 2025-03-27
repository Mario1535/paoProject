#include "mediaeditor.h"
#include "ui_mediaeditor.h"
#include <QFileDialog>
#include <QMessageBox>
#include "podcast.h"
#include "music.h"
#include "audiobook.h"

mediaEditor::mediaEditor(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::mediaEditor)
    , currentMedia(nullptr)
{
    ui->setupUi(this);

    // Connessione dei pulsanti
    connect(ui->saveButton, &QPushButton::clicked, this, &mediaEditor::onSaveButtonClicked);
    connect(ui->closeButton, &QPushButton::clicked, this, &mediaEditor::onCancelButtonClicked);
    connect(ui->photoButton, &QPushButton::clicked, this, &mediaEditor::onChangePhotoButtonClicked);
}

mediaEditor::~mediaEditor()
{
    delete ui;
}

void mediaEditor::loadMedia(AbstractMedia *media) {
    currentMedia = media;
    ui->photoLabel->setPixmap(QPixmap(QString::fromStdString(media->getImagePath())).scaled(200, 200, Qt::KeepAspectRatio));
    ui->titleLine->setText(QString::fromStdString(media->getTitle()));
    ui->authorLine->setText(QString::fromStdString(media->getAuthor()));
    ui->yearLine->setText(QString::number(media->getYear()));
    ui->durationLine->setText(QString::number(media->getDuration()));

    if (auto audiobook = dynamic_cast<Audiobook*>(media)) {
        ui->stackedWidget->setCurrentIndex(0);  // Audiolibro
        ui->readerLine->setText(QString::fromStdString(audiobook->getReader()));
        //summaryButton
    } else if (auto music = dynamic_cast<Music*>(media)) {
        ui->stackedWidget->setCurrentIndex(1);  // Musica
        ui->albumLine->setText(QString::fromStdString(music->getAlbum()));
        //lyricsButton
    } else if (auto podcast = dynamic_cast<Podcast*>(media)) {
        ui->stackedWidget->setCurrentIndex(2);  // Podcast
        ui->episodeLine->setText(QString::number(podcast->getEpisode()));
        ui->seasonLine->setText(QString::number(podcast->getSeason()));
    }
}

AbstractMedia* mediaEditor::getMedia() {
    return currentMedia;
}

void mediaEditor::onSaveButtonClicked() {
    // Salva le modifiche e chiudi la finestra
    accept();
}

void mediaEditor::onCancelButtonClicked() {
    // Chiudi la finestra senza salvare
    reject();
}

void mediaEditor::onChangePhotoButtonClicked() {
    QString newPhotoPath = QFileDialog::getOpenFileName(this, "Seleziona una foto", "", "Immagini (*.png *.jpg *.jpeg)");
    if (!newPhotoPath.isEmpty()) {
        photoPath = newPhotoPath;
        ui->photoLabel->setPixmap(QPixmap(photoPath).scaled(200, 200, Qt::KeepAspectRatio));
    }
}
