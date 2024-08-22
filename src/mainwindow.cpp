/*
 * Copyright 2024 AliTech Works
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mainwindow.h"
#include "qdialog.h"
#include "ui_mainwindow.h"

#include <QSpinBox>
#include <QFile>
#include <QTextStream>
#include <QMouseEvent>

#include <random>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QString statusBarMessage = "Sudoku - by AliTech Works v1.0";
    ui->statusBar->setSizeGripEnabled(false);
    ui->statusBar->setStyleSheet("border-top: 1px outset grey;");
    ui->statusBar->showMessage(statusBarMessage);

    for (int i = 1; i <= 81; i++) {
        QString frameObjectName = QString("frame_%1").arg(i, 2, 10, QChar('0'));
        QString labelObjectName = QString("label_%1").arg(i, 2, 10, QChar('0'));

        QFrame *frame = qobject_cast<QFrame*>(ui->centralwidget->findChild<QObject*>(frameObjectName));
        QLabel *label = qobject_cast<QLabel*>(ui->centralwidget->findChild<QObject*>(labelObjectName));

        frame->setStyleSheet("background-color: white; border: 1px solid black;");
        label->setStyleSheet("border: none;");
    }

    ui-> possibleSolutions_label->setEnabled(false);
    ui->findPossibleSolutions_pushButton->setEnabled(false);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::startNewGame(int brojOtkrivenihPolja) {
    QFont mainFont;
    mainFont.setPointSize(20);
    mainFont.setBold(true);

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distribution(1, 1000);

    QList<int> newGameSolutions;

    int randomNumber = distribution(gen);
    int targetLineNumber = randomNumber;

    QString filePath = ":/sudoku_solutions/sudoku_solutions.txt";

    QFile file(filePath);

    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&file);

    for (int currentLineNumber = 1; currentLineNumber < targetLineNumber && !in.atEnd(); ++currentLineNumber) {
        in.readLine();
    }

    if (!in.atEnd()) {
        QString line = in.readLine();

        if (line.startsWith("{") && line.endsWith("}")) {
            line = line.mid(1, line.length() - 2);
        }

        QStringList numberStrings = line.split(", ", Qt::SkipEmptyParts);
        for (const QString& numberString : numberStrings) {
            newGameSolutions.append(numberString.toInt());
        }
    }

    file.close();

    for (int i = 1; i <= 81; i++) {
        QString labelObjectName = QString("label_%1").arg(i, 2, 10, QChar('0'));
        QLabel *label = qobject_cast<QLabel*>(ui->centralwidget->findChild<QObject*>(labelObjectName));

        label->setText(QString::number(newGameSolutions[i-1]));

        label->setFont(mainFont);
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("color: black; border: none;");
    }

    QList <int> deletedFrames;

    for (int i = 0; i < 81 - brojOtkrivenihPolja; i++) {
        std::uniform_int_distribution<> distribution(1, 81);

        int randomNumber = distribution(gen);

        if (!deletedFrames.contains(randomNumber)) {
            QString labelObjectName = QString("label_%1").arg(randomNumber, 2, 10, QChar('0'));
            QLabel *label = qobject_cast<QLabel*>(ui->centralwidget->findChild<QObject*>(labelObjectName));

            label->clear();
        } else {
            i--;
        }

        deletedFrames.append(randomNumber);
    }

    for (int i = 1; i <= 81; i++) {
        QString frameObjectName = QString("frame_%1").arg(i, 2, 10, QChar('0'));
        QFrame *frame = qobject_cast<QFrame*>(ui->centralwidget->findChild<QObject*>(frameObjectName));

        QString labelObjectName = QString("label_%1").arg(i, 2, 10, QChar('0'));
        QLabel *label = qobject_cast<QLabel*>(ui->centralwidget->findChild<QObject*>(labelObjectName));

        if (label->text() != "") {
            gameGeneratedFrames.append(frame->objectName());
        }
    }

    newGameSolutions.clear();
    deletedFrames.clear();
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (clickedFrame && !errorFrames.contains(clickedFrame->objectName())) {
        clickedFrame->setStyleSheet("background-color: white; border: 1px solid black;");
    } else if (clickedFrame && errorFrames.contains(clickedFrame->objectName())) {
        clickedFrame->setStyleSheet("background-color: #ff3333; border: 1px solid black;");
    }

    for (int i = 1; i <= 81; i++) {
        QString frameObjectName = QString("frame_%1").arg(i, 2, 10, QChar('0'));
        QFrame *frame = qobject_cast<QFrame*>(ui->centralwidget->findChild<QObject*>(frameObjectName));

        if (frame->geometry().contains(event->pos()) && !gameGeneratedFrames.contains(frame->objectName())) {
            if (!errorFrames.contains(frame->objectName())) {
                frame->setStyleSheet("background-color: #fff700; border: 1px solid black;");
                frame->setFocus();

                frameClicked = true;
                labelInputEnabled = true;
                clickedFrame = frame;

                ui-> possibleSolutions_label->setEnabled(false);
                ui->solutions_label->clear();
                ui->findPossibleSolutions_pushButton->setEnabled(true);
            } else {
                frame->setStyleSheet("background-color: #ff9900; border: 1px solid black;");
                frame->setFocus();

                frameClicked = true;
                labelInputEnabled = true;
                clickedFrame = frame;

                ui-> possibleSolutions_label->setEnabled(false);
                ui->solutions_label->clear();
                ui->findPossibleSolutions_pushButton->setEnabled(true);
            }

            return;
        } else {
            frameClicked = false;
            labelInputEnabled = false;
            clickedFrame = nullptr;

            ui-> possibleSolutions_label->setEnabled(false);
            ui->solutions_label->clear();
            ui->findPossibleSolutions_pushButton->setEnabled(false);
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    QFont mainFont;
    mainFont.setPointSize(20);
    mainFont.setBold(true);

    for (int i = 1; i <= 81; i++) {
        QString frameObjectName = QString("frame_%1").arg(i, 2, 10, QChar('0'));
        QString labelObjectName = QString("label_%1").arg(i, 2, 10, QChar('0'));

        QFrame *frame = qobject_cast<QFrame*>(ui->centralwidget->findChild<QObject*>(frameObjectName));
        QLabel *label = qobject_cast<QLabel*>(ui->centralwidget->findChild<QObject*>(labelObjectName));

        if (frame->hasFocus() && !gameGeneratedFrames.contains(frame->objectName()) && labelInputEnabled ) {
            if (event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Delete) {
                label->clear();

                checkFrames();

                if (errorFrames.contains(frame->objectName())) {
                    errorFrames.removeOne(frame->objectName());
                }

                frame->setStyleSheet("background-color: white; border: 1px solid black;");

                frameClicked = false;
                labelInputEnabled = false;
                clickedFrame = nullptr;

                ui-> possibleSolutions_label->setEnabled(false);
                ui->solutions_label->clear();
                ui->findPossibleSolutions_pushButton->setEnabled(false);
            } else if (event->text().toInt() != 0) {
                QString labelText = QString::number(event->text().toInt());
                label->setText(labelText);

                label->setFont(mainFont);
                label->setAlignment(Qt::AlignCenter);
                label->setStyleSheet("color: blue; border: none;");

                checkSolution();
                checkFrames();
            }

            return;
        }
    }
}

QList <int> MainWindow::findPossibleSolutions() {
    int x;
    int y;
    int sectionOfTheFrame;

    QList <int> possibleSolutions = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    QList<QList<QFrame*>> sections;

    for (int i = 0; i < 9; i++) {
        QList<QFrame*> section;

        for (int j = 0; j < 9; j++) {
            int frameNumber = i * 9 + j + 1;
            QFrame *frame = new QFrame;
            frame->setObjectName(QString("frame_%1").arg(frameNumber, 2, 10, QChar('0')));

            section.append(frame);

            if (frame->objectName() == clickedFrame->objectName()) {
                sectionOfTheFrame = i;
            }
        }

        sections.append(section);
    }

    for (auto frameName : sections[sectionOfTheFrame]) {
        QFrame *frame = this->findChild<QFrame*>(frameName->objectName());

        QLabel *label = frame->findChild<QLabel*>();

        QString labelText = label->text();

        QTextDocument textDocument;
        textDocument.setHtml(labelText);
        QString plainText = textDocument.toPlainText();

        if (frame->objectName() == clickedFrame->objectName()) {
            continue;
        }

        if (possibleSolutions.contains(plainText.toInt())) {
            possibleSolutions.removeOne(plainText.toInt());
        }
    }

    QList<QList<QFrame*>> frameTable;

    int blockSize = 3;
    int totalSections = 9;
    int startingPoint = 0;

    for (int i = 0; i < totalSections; i += blockSize) {
        for (int j = 0; j < blockSize; ++j) {
            QList<QFrame*> column;

            for (int sectionNumber = i; sectionNumber < i + blockSize; ++sectionNumber) {
                for (int k = startingPoint; k < blockSize + startingPoint; ++k) {
                    QFrame *frame = sections[sectionNumber][k];
                    column.append(frame);
                }
            }

            frameTable.append(column);
            startingPoint += blockSize;
        }

        startingPoint = 0;
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (frameTable[i][j]->objectName() == clickedFrame->objectName()) {
                x = i;
                y = j;
            }
        }
    }

    for (int i = 0; i < 9; i++) {
        QFrame *frame = this->findChild<QFrame*>(frameTable[x][i]->objectName());

        QLabel *label = frame->findChild<QLabel*>();

        QString labelText = label->text();

        QTextDocument textDocument;
        textDocument.setHtml(labelText);
        QString plainText = textDocument.toPlainText();

        if (frame->objectName() == clickedFrame->objectName()) {
            continue;
        }

        if (possibleSolutions.contains(plainText.toInt())) {
            possibleSolutions.removeOne(plainText.toInt());
        }
    }

    for (int i = 0; i < 9; i++) {
        QFrame *frame = this->findChild<QFrame*>(frameTable[i][y]->objectName());

        QLabel *label = frame->findChild<QLabel*>();

        QString labelText = label->text();

        QTextDocument textDocument;
        textDocument.setHtml(labelText);
        QString plainText = textDocument.toPlainText();

        if (frame->objectName() == clickedFrame->objectName()) {
            continue;
        }

        if (possibleSolutions.contains(plainText.toInt())) {
            possibleSolutions.removeOne(plainText.toInt());
        }
    }

    sections.clear();
    frameTable.clear();

    return possibleSolutions;
}

void MainWindow::checkSolution() {
    QList <int> possibleSolutions = findPossibleSolutions();

    QFrame *frame = clickedFrame;

    QLabel *label = frame->findChild<QLabel*>();
    QString labelText = label->text();

    QTextDocument textDocument;
    textDocument.setHtml(labelText);
    QString plainText = textDocument.toPlainText();

    if (possibleSolutions.contains(plainText.toInt())) {
        frame->setStyleSheet("background-color: white; border: 1px solid black;");

        if (errorFrames.contains(frame->objectName())) {
            errorFrames.removeOne(frame->objectName());
        }

        frameClicked = false;
        labelInputEnabled = false;
        clickedFrame = nullptr;

        ui-> possibleSolutions_label->setEnabled(false);
        ui->solutions_label->clear();
        ui->findPossibleSolutions_pushButton->setEnabled(false);
    } else {
        frame->setStyleSheet("background-color: #ff3333; border: 1px solid black;");
        label->setStyleSheet("color: blue; border: none;");

        frameClicked = false;
        labelInputEnabled = false;

        if (!errorFrames.contains(clickedFrame->objectName())) {
            errorFrames.append(clickedFrame->objectName());
        }

        clickedFrame = nullptr;

        ui-> possibleSolutions_label->setEnabled(false);
        ui->solutions_label->clear();
        ui->findPossibleSolutions_pushButton->setEnabled(false);
    }
}

void MainWindow::checkFrames() {
    for (const QString& frameObjectName : errorFrames) {
        QFrame *frame = qobject_cast<QFrame*>(ui->centralwidget->findChild<QObject*>(frameObjectName));

        clickedFrame = frame;
        checkSolution();
    }
}

void MainWindow::on_findPossibleSolutions_pushButton_clicked() {
    QList <int> possibleSolutions = findPossibleSolutions();

    ui-> possibleSolutions_label->setEnabled(true);

    QString possibleSolutionsText;

    if (!possibleSolutions.isEmpty()) {
        std::string z = "";

        for (int solution : possibleSolutions) {
            possibleSolutionsText += z + std::to_string(solution);

            z = ", ";
        }
    } else {
        possibleSolutionsText = "There is no solution";
    }

    QFont solutionsFont;
    solutionsFont.setPointSize(18);

    ui->solutions_label->setText(possibleSolutionsText);
    ui->solutions_label->setAlignment(Qt::AlignCenter);
    ui->solutions_label->setFont(solutionsFont);

    clickedFrame->setFocus();
}


void MainWindow::on_startNewGame_pushButton_clicked() {
    if (clickedFrame) {
        clickedFrame->setStyleSheet("background-color: white; border: 1px solid black;");
    }

    frameClicked = false;
    labelInputEnabled = false;
    clickedFrame = nullptr;

    ui-> possibleSolutions_label->setEnabled(false);
    ui->solutions_label->clear();
    ui->findPossibleSolutions_pushButton->setEnabled(false);

    QDialog *newGameWindow = new QDialog(this);
    newGameWindow->setFixedSize(300, 80);
    newGameWindow->setWindowTitle("Start new game");

    QLabel *numberOfGivenCellsLabel = new QLabel("Number of given cells: ");

    QSpinBox *numberOfGivenCellsSpinBox = new QSpinBox;
    numberOfGivenCellsSpinBox->setMinimum(20);
    numberOfGivenCellsSpinBox->setMaximum(50);

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    QVBoxLayout *verticalLayout = new QVBoxLayout;

    horizontalLayout->addWidget(numberOfGivenCellsLabel);
    horizontalLayout->addWidget(numberOfGivenCellsSpinBox);

    QPushButton *startButton = new QPushButton("Start");
    startButton->setFocusPolicy(Qt::NoFocus);

    connect(startButton, &QPushButton::clicked, this, [=]() {
        gameGeneratedFrames.clear();
        errorFrames.clear();

        for (int i = 1; i <= 81; i++) {
            QString frameObjectName = QString("frame_%1").arg(i, 2, 10, QChar('0'));
            QString labelObjectName = QString("label_%1").arg(i, 2, 10, QChar('0'));

            QFrame *frame = qobject_cast<QFrame*>(ui->centralwidget->findChild<QObject*>(frameObjectName));
            QLabel *label = qobject_cast<QLabel*>(ui->centralwidget->findChild<QObject*>(labelObjectName));

            frame->setStyleSheet("background-color: white; border: 1px solid black;");
            label->setStyleSheet("border: none;");
        }

        newGameWindow->close();
        startNewGame(numberOfGivenCellsSpinBox->text().toInt());
        newGameWindow->deleteLater();
    });

    verticalLayout->addLayout(horizontalLayout);
    verticalLayout->addWidget(startButton);

    newGameWindow->setLayout(verticalLayout);
    newGameWindow->exec();
}
