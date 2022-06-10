#ifndef PREDICTION_TRIE_UI_H
#define PREDICTION_TRIE_UI_H

#include "PredictionTrie.h"
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QDebug>
#include <QFile>


class UI : public QWidget
{
    Q_OBJECT
public:
    explicit UI(QWidget* parent = nullptr);

private:
    QLineEdit* _inputLine;
    std::array<QLabel*, 5> _predWords;
    QPushButton* _browseBtn;

    QLineEdit* inputLine();
    QWidget* predWordsWidget();
    QPushButton* browseBtn();

    PredictionTrie  _pt;

    QFont font();

private slots:
    void browseDictionary();

    void predictWord(const QString& word);
};

#endif //PREDICTION_TRIE_UI_H
