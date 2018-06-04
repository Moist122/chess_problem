#pragma once

class Between{
public:
    bool operator()(const char x, const char y, const char z) const //check if x<=y<=z
        {return x<=y&&z>=y;}
};