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

#include <QApplication>
#include <QDialog>
#include <QLabel>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.setFixedSize(578, 760);
    window.setWindowTitle("Sudoku");
    window.setWindowIcon(QIcon(":/icons/sudoku.ico"));

    QDialog *newGameWindow = new QDialog();
    newGameWindow->setFixedSize(300, 80);
    newGameWindow->setWindowTitle("Start new game");
    newGameWindow->setWindowIcon(QIcon(":/icons/sudoku.ico"));

    QLabel *numberOfGivenCellsLabel = new QLabel("Number of given cells: ");

    QSpinBox *numberOfGivenCellsSpinBox = new QSpinBox();
    numberOfGivenCellsSpinBox->setMinimum(20);
    numberOfGivenCellsSpinBox->setMaximum(50);

    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    QVBoxLayout *verticalLayout = new QVBoxLayout();

    horizontalLayout->addWidget(numberOfGivenCellsLabel);
    horizontalLayout->addWidget(numberOfGivenCellsSpinBox);

    QPushButton *startButton = new QPushButton("Start");
    startButton->setFocusPolicy(Qt::NoFocus);

    bool start = false;

    std::function<void()> startGame = [&]() {
        start = true;

        newGameWindow->close();

        window.startNewGame(numberOfGivenCellsSpinBox->value());
        window.show();
    };

    QObject::connect(startButton, &QPushButton::clicked, startGame);

    verticalLayout->addLayout(horizontalLayout);
    verticalLayout->addWidget(startButton);

    newGameWindow->setLayout(verticalLayout);
    newGameWindow->exec();

    if (start) {
        return app.exec();
    }
}
