#pragma once
#ifndef COMP_345_CommandProcessing_h
#define COMP_345_CommandProcessing_h

#include <iostream>
#include "../Header Files/LoggingObserver.h"
using namespace std;

enum class GameState {
	start, mapLoaded, mapValidated, playersAdded, assignReinforcement, issueOrders, executeOrders, win
};

class Command :public ILoggable, public Subject {
public:
    Command() = default;
    Command(string cmd);
    ~Command() = default;
    void saveEffect(string e);
    string getEffect() { return effect; }
    string getCommandText() { return command; }
    string stringToLog() override;
private:
    string command;
    string effect;

};


// TARGET
class CommandProcessor : public ILoggable, public Subject {
public:
    CommandProcessor() = default;
    ~CommandProcessor() = default;
    void getCommand();
    string validate(GameState gs);
    string stringToLog() override;
protected:


private:
    virtual string readCommand();
    void saveCommand(const string& cmd);
    list<Command>* lc = new list<Command>();
};

// ADAPTEE
class FileLineReader {
public:
    FileLineReader(const string& filename);
    ~FileLineReader() = default;
    string readLineFromFile();
private:
    ifstream inputFileStream;
};

// ADAPTER
class FileCommandProcessorAdapter : public CommandProcessor {
public:
    FileCommandProcessorAdapter(FileLineReader* flr) { this->flr = flr; }
    ~FileCommandProcessorAdapter() = default;
protected:
    string readCommand();
private:
    FileLineReader* flr;
};
#endif