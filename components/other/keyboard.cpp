#include "components/other/keyboard.h"
#include "ui_keyboard.h"
#include "global.h"

#include <QTimer>
#include <QDebug>

keyboard::keyboard(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::keyboard)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);


    lowerCaseButtons();
    lowerCase = true;
    special = false;
}

keyboard::~keyboard()
{
    delete ui;
}

void keyboard::start(QLineEdit* textEditorToAdd) {
    textEditor = textEditorToAdd;
    moveToPosition();
    mainString = textEditor->text();
    textEditor->setSelection(0,0);
    textEditor->setCursorPosition(textEditor->text().length());
}

void keyboard::moveToPosition() {
    float multiplier = 1.8;
    this->setFixedSize(ereaderVars::screenX, ereaderVars::screenY - ereaderVars::screenY / multiplier);
    this->move(0,  ereaderVars::screenY / multiplier);
}

void keyboard::updateString(QString new_string)
{
    int cursorPosition = textEditor->cursorPosition();
    textEditor->setText(textEditor->text().replace(cursorCharacter, "")); // This resets the position

    textEditor->setText(textEditor->text().insert(cursorPosition, new_string));
    textEditor->setText(textEditor->text().insert(cursorPosition + 1, cursorCharacter));
    textEditor->setCursorPosition(cursorPosition + 1);
}

void keyboard::lowerCaseButtons()
{
    ui->Button_q->setText("q");
    ui->Button_w->setText("w");
    ui->Button_e->setText("e");
    ui->Button_r->setText("r");
    ui->Button_t->setText("t");
    ui->Button_y->setText("y");
    ui->Button_u->setText("u");
    ui->Button_i->setText("i");
    ui->Button_o->setText("o");
    ui->Button_p->setText("p");

    ui->Button_a->setText("a");
    ui->Button_s->setText("s");
    ui->Button_d->setText("d");
    ui->Button_f->setText("f");
    ui->Button_g->setText("g");
    ui->Button_h->setText("h");
    ui->Button_j->setText("j");
    ui->Button_k->setText("k");
    ui->Button_l->setText("l");

    ui->Button_z->setText("z");
    ui->Button_x->setText("x");
    ui->Button_c->setText("c");
    ui->Button_v->setText("v");
    ui->Button_b->setText("b");
    ui->Button_n->setText("n");
    ui->Button_m->setText("m");
}

void keyboard::upperCaseButtons()
{
    ui->Button_q->setText("Q");
    ui->Button_w->setText("W");
    ui->Button_e->setText("E");
    ui->Button_r->setText("R");
    ui->Button_t->setText("T");
    ui->Button_y->setText("Y");
    ui->Button_u->setText("U");
    ui->Button_i->setText("I");
    ui->Button_o->setText("O");
    ui->Button_p->setText("P");

    ui->Button_a->setText("A");
    ui->Button_s->setText("S");
    ui->Button_d->setText("D");
    ui->Button_f->setText("F");
    ui->Button_g->setText("G");
    ui->Button_h->setText("H");
    ui->Button_j->setText("J");
    ui->Button_k->setText("K");
    ui->Button_l->setText("L");

    ui->Button_z->setText("Z");
    ui->Button_x->setText("X");
    ui->Button_c->setText("C");
    ui->Button_v->setText("V");
    ui->Button_b->setText("B");
    ui->Button_n->setText("N");
    ui->Button_m->setText("M");
}

void keyboard::on_Button_Caps_clicked()
{
    // this can be changed in the future for more characters
    if(special == false)
    {
        if(lowerCase == true)
        {
            lowerCase = false;
            upperCaseButtons();
            ui->Button_Caps->setStyleSheet("font-weight: bold");
        } else {
            lowerCase = true;
            lowerCaseButtons();
            ui->Button_Caps->setStyleSheet("font-weight: normal");
        }
    }
}

void keyboard::on_Button_space_clicked()
{
    updateString(" ");
}

void keyboard::on_Button_backspace_clicked()
{
    int cursorPosition = textEditor->cursorPosition();
    textEditor->setText(textEditor->text().replace(cursorCharacter, ""));

    textEditor->setText(textEditor->text().remove(cursorPosition - 1, 1));
    textEditor->setText(textEditor->text().insert(cursorPosition - 1, cursorCharacter));
    textEditor->setCursorPosition(cursorPosition - 1);
}

void keyboard::on_Button_Special_clicked()
{
    if(special == false)
    {
        special = true;
        ui->Button_Special->setStyleSheet("font-weight: bold");
        ui->Button_q->setText("1");
        ui->Button_w->setText("2");
        ui->Button_e->setText("3");
        ui->Button_r->setText("4");
        ui->Button_t->setText("5");
        ui->Button_y->setText("6");
        ui->Button_u->setText("7");
        ui->Button_i->setText("8");
        ui->Button_o->setText("9");
        ui->Button_p->setText("0");
        ui->Button_Cancel->setIcon(QIcon(":/icons/left.svg"));
        ui->Button_Confirm->setIcon(QIcon(":/icons/right.svg"));

        ui->Button_v->setText(":");
        ui->Button_m->setText("/");
    } else {
        special = false;
        ui->Button_Special->setStyleSheet("font-weight: normal");
        ui->Button_Cancel->setIcon(QIcon(":/icons/close.png"));
        ui->Button_Confirm->setIcon(QIcon(":/icons/confirm.svg"));
        if(lowerCase == true)
        {
            lowerCaseButtons();
        } else {
            upperCaseButtons();
        }
    }
}

void keyboard::on_Button_Cancel_clicked()
{
    if(special == true) {
        qDebug() << "Cursor backwards";
        int cursorPosition = textEditor->cursorPosition() - 1;
        textEditor->setText(textEditor->text().replace(cursorCharacter, ""));

        textEditor->setText(textEditor->text().insert(cursorPosition, cursorCharacter));
        textEditor->setCursorPosition(cursorPosition);
    } else {
        textEditor->setText(mainString);
        textEditor->setText(textEditor->text().replace(cursorCharacter, ""));
        QString newText = mainString;
        while(newText.endsWith(" ") == true) {
            newText.chop(1);
        }
        textEditor->setText(newText);
        this->close();
    }
}


void keyboard::on_Button_Confirm_clicked()
{
    if(special == true) {
        int cursorPosition = textEditor->cursorPosition() + 1;
        textEditor->setText(textEditor->text().replace(cursorCharacter, ""));

        textEditor->setText(textEditor->text().insert(cursorPosition, cursorCharacter));
        textEditor->setCursorPosition(cursorPosition);
    } else {
        textEditor->setText(textEditor->text().replace(cursorCharacter, ""));
        QString newText = textEditor->text();
        while(newText.endsWith(" ") == true) {
            newText.chop(1);
        }
        textEditor->setText(newText);
        this->close();
    }
}

///

void keyboard::on_Button_q_clicked()
{
    updateString(ui->Button_q->text());
}

void keyboard::on_Button_w_clicked()
{
    updateString(ui->Button_w->text());
}

void keyboard::on_Button_e_clicked()
{
    updateString(ui->Button_e->text());
}

void keyboard::on_Button_r_clicked()
{
    updateString(ui->Button_r->text());
}

void keyboard::on_Button_t_clicked()
{
    updateString(ui->Button_t->text());
}

void keyboard::on_Button_y_clicked()
{
    updateString(ui->Button_y->text());
}

void keyboard::on_Button_u_clicked()
{
    updateString(ui->Button_u->text());
}

void keyboard::on_Button_i_clicked()
{
    updateString(ui->Button_i->text());
}

void keyboard::on_Button_o_clicked()
{
    updateString(ui->Button_o->text());
}

void keyboard::on_Button_p_clicked()
{
    updateString(ui->Button_p->text());
}

///

void keyboard::on_Button_a_clicked()
{
    updateString(ui->Button_a->text());
}

void keyboard::on_Button_s_clicked()
{
    updateString(ui->Button_s->text());
}

void keyboard::on_Button_d_clicked()
{
    updateString(ui->Button_d->text());
}

void keyboard::on_Button_f_clicked()
{
    updateString(ui->Button_f->text());
}

void keyboard::on_Button_g_clicked()
{
    updateString(ui->Button_g->text());
}

void keyboard::on_Button_h_clicked()
{
    updateString(ui->Button_h->text());
}

void keyboard::on_Button_j_clicked()
{
    updateString(ui->Button_j->text());
}

void keyboard::on_Button_k_clicked()
{
    updateString(ui->Button_k->text());
}

void keyboard::on_Button_l_clicked()
{
    updateString(ui->Button_l->text());
}

///

void keyboard::on_Button_z_clicked()
{
    updateString(ui->Button_z->text());
}

void keyboard::on_Button_x_clicked()
{
    updateString(ui->Button_x->text());
}

void keyboard::on_Button_c_clicked()
{
    updateString(ui->Button_c->text());
}

void keyboard::on_Button_v_clicked()
{
    updateString(ui->Button_v->text());
}

void keyboard::on_Button_b_clicked()
{
    updateString(ui->Button_b->text());
}

void keyboard::on_Button_n_clicked()
{
    updateString(ui->Button_n->text());
}

void keyboard::on_Button_m_clicked()
{
    updateString(ui->Button_m->text());
}

void keyboard::on_Button_dot_clicked()
{
    updateString(ui->Button_dot->text());
}

