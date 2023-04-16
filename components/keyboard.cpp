#include "components/keyboard.h"
#include "ui_keyboard.h"
#include "globals.h"

keyboard::keyboard(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::keyboard)
{
    ui->setupUi(this);

    int y = (ereaderVars::screen_y / 2);
    this->move(0, y);
    this->setMinimumSize(ereaderVars::screen_x, y);
    this->adjustSize();

    ui->lineEdit->setVisible(false);
    lower_case_buttons();
    lower_case = true;
    special = false;
}

keyboard::~keyboard()
{
    delete ui;
}

// TODO remove this
void keyboard::update_string(QString new_string)
{
    edited_string.remove("|");

    edited_string.insert(cursor_main, new_string);

    emit update_data(edited_string, cursor_main);
}

void keyboard::lower_case_buttons()
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

void keyboard::upper_case_buttons()
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
        if(lower_case == true)
        {
            lower_case = false;
            upper_case_buttons();
            ui->Button_Caps->setStyleSheet("font-weight: bold");
        } else {
            lower_case = true;
            lower_case_buttons();
            ui->Button_Caps->setStyleSheet("font-weight: normal");
        }
    }
}

void keyboard::on_Button_space_clicked()
{
    update_string(" ");
}

void keyboard::on_Button_backspace_clicked()
{
    edited_string.remove("|");

    if(cursor_main != 0)
    {
        cursor_main = cursor_main - 1;
    }
    QString new_string = edited_string.remove(cursor_main, 1);
    edited_string = new_string;
    update_string("");
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
        ui->Button_Cancel->setText("⟵");
        ui->Button_Confirm->setText("⟶");
    } else {
        special = false;
        ui->Button_Special->setStyleSheet("font-weight: normal");
        ui->Button_Cancel->setText("Cancel");
        ui->Button_Confirm->setText("Confirm");
        if(lower_case == true)
        {
            lower_case_buttons();
        } else {
            upper_case_buttons();
        }
    }
}

void keyboard::on_Button_Cancel_clicked()
{
    if(ui->Button_Cancel->text() == "Cancel")
    {
        emit update_data(main_string, 0);
        emit keyboard_closed(false);
        this->close();
    } else {
        cursor_main = cursor_main - 1;
        emit update_data(edited_string, cursor_main);
    }
}


void keyboard::on_Button_Confirm_clicked()
{
    if(ui->Button_Confirm->text() == "Confirm")
    {
        edited_string.remove("|");
        emit keyboard_closed(true);
        this->close();
    } else {
        cursor_main = cursor_main + 1;
        edited_string.remove("|");
        emit update_data(edited_string, cursor_main);
    }
}

///

void keyboard::on_Button_q_clicked()
{
    update_string(ui->Button_q->text());
}

void keyboard::on_Button_w_clicked()
{
    update_string(ui->Button_w->text());
}


void keyboard::on_Button_e_clicked()
{
    update_string(ui->Button_e->text());
}


void keyboard::on_Button_r_clicked()
{
    update_string(ui->Button_r->text());
}

void keyboard::on_Button_t_clicked()
{
    update_string(ui->Button_t->text());
}

void keyboard::on_Button_y_clicked()
{
    update_string(ui->Button_y->text());
}

void keyboard::on_Button_u_clicked()
{
    update_string(ui->Button_u->text());
}

void keyboard::on_Button_i_clicked()
{
    update_string(ui->Button_i->text());
}

void keyboard::on_Button_o_clicked()
{
    update_string(ui->Button_o->text());
}

void keyboard::on_Button_p_clicked()
{
    update_string(ui->Button_p->text());
}

///

void keyboard::on_Button_a_clicked()
{
    update_string(ui->Button_a->text());
}

void keyboard::on_Button_s_clicked()
{
    update_string(ui->Button_s->text());
}

void keyboard::on_Button_d_clicked()
{
    update_string(ui->Button_d->text());
}

void keyboard::on_Button_f_clicked()
{
    update_string(ui->Button_f->text());
}

void keyboard::on_Button_g_clicked()
{
    update_string(ui->Button_g->text());
}

void keyboard::on_Button_h_clicked()
{
    update_string(ui->Button_h->text());
}

void keyboard::on_Button_j_clicked()
{
    update_string(ui->Button_j->text());
}

void keyboard::on_Button_k_clicked()
{
    update_string(ui->Button_k->text());
}

void keyboard::on_Button_l_clicked()
{
    update_string(ui->Button_l->text());
}

///

void keyboard::on_Button_z_clicked()
{
    update_string(ui->Button_z->text());
}

void keyboard::on_Button_x_clicked()
{
    update_string(ui->Button_x->text());
}

void keyboard::on_Button_c_clicked()
{
    update_string(ui->Button_c->text());
}

void keyboard::on_Button_v_clicked()
{
    update_string(ui->Button_v->text());
}

void keyboard::on_Button_b_clicked()
{
    update_string(ui->Button_b->text());
}

void keyboard::on_Button_n_clicked()
{
    update_string(ui->Button_n->text());
}

void keyboard::on_Button_m_clicked()
{
    update_string(ui->Button_m->text());
}

void keyboard::on_Button_dot_clicked()
{
    update_string(ui->Button_m->text());
}

