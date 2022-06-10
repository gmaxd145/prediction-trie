#include "UI.h"

UI::UI(QWidget* parent) : QWidget(parent), _inputLine(new QLineEdit), _browseBtn(new QPushButton)
{
    QVBoxLayout* mainLayout = new QVBoxLayout;

    mainLayout->addWidget(inputLine());
    mainLayout->addWidget(predWordsWidget());
    mainLayout->addWidget(browseBtn());

    setLayout(mainLayout);

    setWindowTitle("Prediction Trie");
}

QLineEdit* UI::inputLine()
{
    _inputLine->setReadOnly(true);
    _inputLine->setText("Browse dictionary to start");
    _inputLine->setMinimumWidth(500);
    _inputLine->setFont(font());

    connect(_inputLine, SIGNAL(textChanged(const QString&)), this, SLOT(predictWord(const QString&)));

    return _inputLine;
}

QWidget* UI::predWordsWidget()
{
    QWidget* predWordsWidget = new QWidget();
    QVBoxLayout* predWordsWidgetLayout = new QVBoxLayout;

    for (auto& word : _predWords)
    {
        word = new QLabel();
    }

    for (auto& word : _predWords)
    {
        word->setFont(font());
    }

    for (auto& word : _predWords)
    {
        predWordsWidgetLayout->addWidget(word);
    }
    predWordsWidget->setLayout(predWordsWidgetLayout);

    return predWordsWidget;
}

QPushButton *UI::browseBtn()
{
    _browseBtn->setText("Browse");
    _browseBtn->setFont(font());

    connect(_browseBtn,SIGNAL(clicked()), SLOT(browseDictionary()));

    return _browseBtn;
}


QFont UI::font()
{
    QFont font;
    font.setPointSize(font.pointSize() + 6);

    return font;
}

void UI::browseDictionary()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Dictionary", "", "*.txt");


    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        _inputLine->setReadOnly(true);
        _inputLine->setText("Browse dictionary to start");
        return;
    }

    _pt.~PredictionTrie();

    QTextStream in(&file);
    while(!in.atEnd())
    {
        _pt.insert(in.readLine().toStdString());
    }
    _inputLine->setText("");
    _inputLine->setReadOnly(false);
}

void UI::predictWord(const QString& word) {
    if (word == "")
    {
        for (auto& predWord : _predWords)
        {
            predWord->setText("");
        }
        return;
    }
    auto words = _pt.findBestMatches(word.toStdString(), 5);
    for (int i = 0; i < words.size(); ++i) {
        _predWords[i]->setText(QString::fromStdString(words[i]));
    }
    for (int i = words.size(); i < _predWords.size(); ++i) {
        _predWords[i]->setText("");
    }
}
