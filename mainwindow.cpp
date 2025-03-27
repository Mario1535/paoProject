#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "abstractmedia.h"  // Includi le tue classi media
#include "mediawidget.h"    // Widget per visualizzare i media
#include "mediaeditor.h"      // Finestra di modifica/creazione media
#include "mediadetailwidget.h"

class mediaEditor;
class mediaWidget;
class mediaDetailWidget;
class mediaTextOverlay;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connessione della barra di ricerca
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &MainWindow::onSearchTextChanged);

    // Connessione dei menu
    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::onLoadActionTriggered);
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::onNewActionTriggered);
    connect(ui->actionEdit, &QAction::triggered, this, &MainWindow::onEditActionTriggered);
    connect(ui->actionRemove, &QAction::triggered, this, &MainWindow::onRemoveActionTriggered);
    connect(ui->actionHelp, &QAction::triggered, this, &MainWindow::onHelpActionTriggered);

    // Carica i media
    loadMedia();
}

MainWindow::~MainWindow()
{
    delete ui;
}



//Mainwindow Menubar
void MainWindow::onLoadActionTriggered() {
    QString filePath = QFileDialog::getOpenFileName(this, "Carica media", "", "File di media (*.json)");
    if (!filePath.isEmpty()) {
        // Carica i media dal file
        loadMediaFromFile(filePath);
    }
}

void MainWindow::onNewActionTriggered() {
    mediaEditor editor(this);
    if (editor.exec() == QDialog::Accepted) {
        AbstractMedia *newMedia = editor.getMedia();
        mediaList.append(newMedia);
        loadMedia();  // Ricarica i media
    }
}

void MainWindow::onEditActionTriggered() {
    // Trova il media selezionato (ad esempio, tramite un indice o un puntatore)
    AbstractMedia *selectedMedia = getSelectedMedia();
    if (selectedMedia) {
        mediaEditor editor(this);
        editor.loadMedia(selectedMedia);
        if (editor.exec() == QDialog::Accepted) {
            loadMedia();  // Ricarica i media
        }
    }
}

void MainWindow::onRemoveActionTriggered() {
    // Trova il media selezionato
    AbstractMedia *selectedMedia = getSelectedMedia();
    if (selectedMedia) {
        mediaList.removeOne(selectedMedia);
        delete selectedMedia;
        loadMedia();  // Ricarica i media
    }
}

void MainWindow::onHelpActionTriggered() {
    QMessageBox::information(this, "Aiuto", "Scorciatoie:\n"
                                            "Ctrl+N: Nuovo media\n"
                                            "Ctrl+E: Modifica media\n"
                                            "Ctrl+D: Rimuovi media\n"
                                            "Ctrl+S: Salva modifiche");
}



//Search bar
void MainWindow::onSearchTextChanged(const QString &text) {
    clearGridLayout();

    for (AbstractMedia *media : mediaList) {
        //modificato, converto in qstring e poi utilizzo contains
        if ((QString::fromStdString(media->getTitle())).contains(text, Qt::CaseInsensitive)) {
            mediaWidget *mediawidget = new mediaWidget(media, this);
            connect(mediawidget, &mediaWidget::clicked, this, &MainWindow::onMediaClicked);
            ui->gridLayout->addWidget(mediawidget);
        }
    }
}



//show media detail and clear grid layout
void MainWindow::onMediaClicked(AbstractMedia *media) {
    mediaDetailWidget *detailWidget = new mediaDetailWidget(this);
    detailWidget->loadMediaDetails(media);
    detailWidget->show();
}

void MainWindow::clearGridLayout() {
    QLayoutItem *item;
    while ((item = ui->gridLayout->takeAt(0))) {
        delete item->widget();
        delete item;
    }
}



//Popolo la main window con i mediawidget tramite funzione load
void MainWindow::loadMedia() {
    clearGridLayout();  // Svuota la griglia prima di ricaricare i media

    for (AbstractMedia *media : mediaList) {
        mediaWidget *mediawidget = new mediaWidget(media, this);
        connect(mediawidget, &mediaWidget::clicked, this, &MainWindow::onMediaClicked);
        ui->gridLayout->addWidget(mediawidget);
    }
}



//gestione chiusura mediaeditor
void MainWindow::closeEvent(QCloseEvent *event) {
    if (hasUnsavedChanges()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Modifiche non salvate",
                                      "Ci sono modifiche non salvate. Vuoi salvare prima di uscire?",
                                      QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (reply == QMessageBox::Save) {
            saveChanges();
        } else if (reply == QMessageBox::Cancel) {
            event->ignore();
            return;
        }
    }
    event->accept();
}

bool MainWindow::hasUnsavedChanges() const {
    // Implementa la logica per verificare se ci sono modifiche non salvate
    return false;
}

void MainWindow::saveChanges() {
    // Implementa la logica per salvare le modifiche
}




//DA IMPLEMENTARE

void MainWindow::loadMediaFromFile(const QString &filePath) {}
AbstractMedia* MainWindow::getSelectedMedia() const { return nullptr; }
