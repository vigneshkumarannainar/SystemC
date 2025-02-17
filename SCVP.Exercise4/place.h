#ifndef PLACE_H
#define PLACE_H

#include <systemc.h>

class placeInterface : public sc_interface {
public:
    virtual void addTokens(unsigned int n) = 0;
    virtual void removeTokens(unsigned int n) = 0;
    virtual unsigned int testTokens() = 0;
};

class place : public placeInterface {
private:
    unsigned int tokens;

public:
    place(unsigned int initial_tokens = 0) : tokens(initial_tokens) {}

    void addTokens(unsigned int n) override { tokens += n; }
    void removeTokens(unsigned int n) override { if (tokens >= n) tokens -= n; }
    unsigned int testTokens() override { return tokens; }
};

#endif
