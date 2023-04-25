#pragma once

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

#include "SecondaryFunction.h"
/*
class LogMessage
{
public:
    //Type type() const;
    const std::string& message() const;
};
*/

class View // Базовый класс окошка, которое видит пользователь
{
public:
    View(int x, int y, int width, int height) // Кординаты позиции на экране и размер окошка
        : x_(x), y_(y), width_(width), height_(height) {}
    virtual ~View() = default;
    
    bool containsClick(int x, int y) const // Определяем пришёлся ли клик в окошко
    {
        return x >= x_ && x <= x_ + width_ && y >= y_ && y <= y_ + height_;
    }
    
    void addSubview(std::unique_ptr<View> view) // Встраиваем другое окошко поверх текущего
    {
        view->parent_ = this;
        subviews_.push_back(std::move(view));
    }
    
    void handleClick(int x, int y)
    {
        if (containsClick(x, y))
        {
            std::wcout << L"Clicked view " << this << L" at " << x << L":" << y << std::endl;
            onClick(); // Обрабатываем клик если он пришёлся в это окошко
            return;
        }
        if (parent_) parent_->handleClick(x, y); // Иначе пробрасываем клик в родительское окошко
    }
    virtual void onClick() {} // Обработка клика переопределяется в классах-наследниках

private:
    std::vector<std::unique_ptr<View>> subviews_;
    View* parent_ = nullptr;
    int x_ = 0;
    int y_ = 0;
    int width_ = 0;
    int height_ = 0;
};

class Button : public View
{
public:
    Button(int x, int y, int width, int height) : View(x, y, width, height) {}
    void onClick() override
    {
        std::wcout << L"Clicked button " << this << std::endl;
    }
};
