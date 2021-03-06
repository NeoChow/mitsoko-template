
#include "View.hpp"

#include <iostream>

using std::cout;
using std::endl;

using android::app::AlertDialog;
using android::support::v7::app::AppCompatActivity;
using android::graphics::Color;

using namespace Mitsoko;

const std::string Modules::Start::View::viewName =
#ifdef __APPLE__
"StartViewController";
#else
"org/mitsokoframework/mitsoko_android/StartActivity";
#endif

void Modules::Start::View::init(){
#ifdef __APPLE__
    UI::ViewController vc(handle);
    vc.view().setBackgroundColor(UI::Color::magentaColor());
    mainBtn().setOnTouchUpInside(std::bind(mainBtnTouched), this);
#else
    editText().getRootView().setBackgroundColor(Color::MAGENTA());
    mainBtn().setOnClickListener(std::bind(mainBtnTouched), *this);
#endif
}

void Modules::Start::View::setTitle(const std::string &value) {
#ifdef __APPLE__
    UI::ViewController vc(handle);
    vc.navigationItem().setTitle(value);
#else
    AppCompatActivity activity(handle);
    activity.getSupportActionBar().setTitle(value);
#endif
}

void Modules::Start::View::setMainBtnTitle(const std::string &value) {
#ifdef __APPLE__
    mainBtn().setTitle(value, UI::Control::State::Normal);
#else
    mainBtn().setText(value);
#endif
}

std::string Modules::Start::View::textFromTextField() {
#ifdef __APPLE__
    return textField().text();
#else
    return editText().getText().toString().c_str();
#endif
}

void Modules::Start::View::showAlert(const std::string &title, const std::string &message, std::function<void()> dismissedCallback) {
#ifdef __APPLE__
    auto alertView = UI::AlertView::create(title, message, std::string("OK"));
    if(dismissedCallback){
        alertView.setDidDismissWithButtonIndex(std::bind(dismissedCallback));
    }
    alertView.show();
#else
    AppCompatActivity activity(handle);
    auto builder = AlertDialog::Builder::create(activity);
    builder.setTitle(title);
    builder.setMessage(message);
    if(dismissedCallback){
        builder.setPositiveButton(std::string("OK"), std::bind(dismissedCallback));
    }else{
        builder.setPositiveButton(std::string("OK"), {});
    }
    builder.create().show();
#endif
}

void Modules::Start::View::setTextFieldText(const std::string &value) {
#ifdef __APPLE__
    textField().setText(value);
#else
    editText().setText(value);
#endif
}
