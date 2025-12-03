
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

enum enOperationType { Add = 1, Sub, Mult, Div, MixOp };
enum enQuestionLevel { EasyLevel = 1, MedLevel, HardLevel, Mix };

int RandomNumber(int From, int To) {
    int Rand = rand() % (To - From + 1) + From;
    return Rand;
}

short ReadHowManyQuestion() {
    short Number0fQuestions;
    do {
        cout << "How many questions do you want to answer : ";
        cin >> Number0fQuestions;
    } while (Number0fQuestions < 1 || Number0fQuestions > 10);
    return Number0fQuestions;
}

enQuestionLevel ReadQuestionLevel() {
    short QuestionLevel;
    do {
        cout << "Enter Question Level [1] Easy ,[2] Med ,[3] Hard,[4] Mix ? ";
        cin >> QuestionLevel;
    } while (QuestionLevel < 1 || QuestionLevel > 4);
    return (enQuestionLevel)QuestionLevel;
}

enOperationType ReadOpType() {
    short OpType;
    do {
        cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
        cin >> OpType;
    } while (OpType < 1 || OpType > 5);
    return (enOperationType)OpType;
}

int SimpleCalculator(int Number1, int Number2, enOperationType OpType) {
    switch (OpType) {
    case enOperationType::Add:
        return Number1 + Number2;
    case enOperationType::Sub:
        return Number1 - Number2;
    case enOperationType::Mult:
        return Number1 * Number2;
    case enOperationType::Div:
        return Number1 / Number2;
    default:
        return Number1 + Number2;
    }
}

struct stQuestion {
    int Number1 = 0;
    int Number2 = 0;
    enOperationType OperationType;
    enQuestionLevel QuestionLevel;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};

struct stQuizz {
    stQuestion QuestionList[100];
    short Number0fQuestion;
    enQuestionLevel QuestionLevel;
    enOperationType OpType;
    short Number0fWrongAnswers;
    short Number0fRightAnswers;
    bool isPass = false;
};

enOperationType GetRandomOperationType() {
    int op = RandomNumber(1, 4);
    return (enOperationType)op;
}

stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OpType) {
    stQuestion Question;
    if (QuestionLevel == enQuestionLevel::Mix) {
        QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);
    }
    if (OpType == enOperationType::MixOp) {
        OpType = GetRandomOperationType();
    }
    Question.OperationType = OpType;

    switch (QuestionLevel) {
    case enQuestionLevel::EasyLevel:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;

    case enQuestionLevel::MedLevel:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;

    case enQuestionLevel::HardLevel:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;
    }
    return Question;
}

void GenerateQuizzQuestions(stQuizz& Quizz) {
    for (short Question = 0; Question < Quizz.Number0fQuestion; Question++) {
        Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionLevel, Quizz.OpType);
    }
}

string GetOpTypeSymbol(enOperationType OpType) {
    switch (OpType) {
    case enOperationType::Add:
        return "+";
    case enOperationType::Sub:
        return "-";
    case enOperationType::Mult:
        return "*";
    case enOperationType::Div:
        return "/";
    default:
        return "Mix";
    }
}

void PrintQuestion(stQuizz& Quizz, short QuestionNumber) {
    cout << "\n";
    cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.Number0fQuestion << "] \n\n";
    cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
    cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
    cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
    cout << "\n__________" << endl;
}

int ReadQuestionAnswer() {
    int Answer = 0;
    cin >> Answer;
    return Answer;
}

void CorrectTheQuestionsAnswesr(stQuizz& Quizz, short QuestionNumber) {
    if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer) {
        Quizz.QuestionList[QuestionNumber].AnswerResult = false;
        Quizz.Number0fWrongAnswers++;
        cout << "Wrong Answer :( \n";
        cout << "The Right Answer Is: ";
        cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer;
        cout << "\n";
        system("color 4F");
        cout << "\a";
    }
    else {
        Quizz.QuestionList[QuestionNumber].AnswerResult = true;
        Quizz.Number0fRightAnswers++;
        cout << "Right Answer :) \n";
        system("color 2F");
    }
    cout << endl;
}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz) {
    for (short QuestionNumber = 0; QuestionNumber < Quizz.Number0fQuestion; QuestionNumber++) {
        PrintQuestion(Quizz, QuestionNumber);
        Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
        CorrectTheQuestionsAnswesr(Quizz, QuestionNumber);
    }
    Quizz.isPass = (Quizz.Number0fRightAnswers >= Quizz.Number0fWrongAnswers);
}

string GetFinalResultText(bool pass) {
    if (pass)
        return "Pass -:)";
    else
        return "Fail -:(";
}

string GetQuestionLevelText(enQuestionLevel QuestionLevel) {
    string ArrQuestionLevelTxt[4] = { "Easy","Medium","Hard","Mix" };
    return ArrQuestionLevelTxt[QuestionLevel - 1];
}

void PrintQuizzResult(stQuizz Quizz) {
    cout << "\n";
    cout << "-----------------------------------\n\n";
    cout << "Final Result Is " << GetFinalResultText(Quizz.isPass);
    cout << "\n-----------------------------------\n\n";
    cout << "Number Of Question :" << Quizz.Number0fQuestion << "\n";
    cout << "Questions Level    :" << GetQuestionLevelText(Quizz.QuestionLevel) << endl;
    cout << "Operation Type     :" << GetOpTypeSymbol(Quizz.OpType) << endl;
    cout << "Number Of Right Answer :" << Quizz.Number0fRightAnswers << "\n";
    cout << "Number Of Wrong Answer :" << Quizz.Number0fWrongAnswers << "\n";
    cout << "-----------------------------------\n";
}

void ResetScreen() {
    system("cls");
    system("color 0F");
}

void PlayMathGame() {
    stQuizz Quizz;
    Quizz.Number0fRightAnswers = 0;
    Quizz.Number0fWrongAnswers = 0;

    Quizz.Number0fQuestion = ReadHowManyQuestion();
    Quizz.QuestionLevel = ReadQuestionLevel();
    Quizz.OpType = ReadOpType();

    GenerateQuizzQuestions(Quizz);
    AskAndCorrectQuestionListAnswers(Quizz);
    PrintQuizzResult(Quizz);
}

void StartGame() {
    char PlayAgain = 'Y';
    do {
        ResetScreen();
        PlayMathGame();
        cout << endl << "Do you want to play again? (Y/N): ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main() {
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}




