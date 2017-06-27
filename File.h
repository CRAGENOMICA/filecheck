/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   File.h
 * Author: jjene
 *
 * Created on 23 de junio de 2017, 15:03
 */

#ifndef FILE_H
#define FILE_H

#include <string>
#include "CProgress.h"
#include "zutil.h"

class File {
private:
  FILE *file_handle_;
  SGZip gz_;
  
public:
    std::string file_name_;
    std::string allowed_bases_;
    long int file_size_;
    long int first_seq_length_;
    std::string different_bases_;
    std::string extra_bases_;
    CProgress progress_;
    long int num_sequences_;
    long int read_lines_;

public:
    File();
    File(const std::string & file_name, const std::string & allowed_bases);
    File(const File& orig);
    virtual ~File();

public:
    bool startCheck(const std::string & message);
    void endCheck(void);
    
public:
    bool discardLine(long int & count);
    
public:
    static long int getFileSize(const std::string & file_name);
    static std::string translateBases(const std::string & bases);
    
protected:
    bool openFile(void);
    void closeFile(void);
    char getFileChar(void);
    
    void annotateBase(char c);
};

#endif /* FILE_H */

