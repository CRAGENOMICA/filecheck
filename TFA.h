/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TFA.h
 * Author: jjene
 *
 * Created on 23 de junio de 2017, 9:52
 */

#ifndef TFA_H
#define TFA_H

#include <string>
#include "File.h"

class TFA : public File {
public:
    TFA() {}
    TFA(const std::string & file_name, const std::string & allowed_bases);
    virtual ~TFA();
    
private:
    bool getSequenceInfo(long int &seq_length, long int & read_bytes);
    
public:
    void check(void);
};

#endif /* TFA_H */

