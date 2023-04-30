#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QDialog>

namespace Ui {
class keyboard;
}

class keyboard : public QDialog
{
    Q_OBJECT

public:
    explicit keyboard(QDialog *parent = nullptr);
    ~keyboard();
    QString main_string;
    QString edited_string;
    int cursor_main;

signals:
    void update_data(QString string, int cursor);
    void keyboard_closed(bool save_string);

private slots:
    void update_string(QString new_string);
    void lower_case_buttons();
    void upper_case_buttons();
    void on_Button_Caps_clicked();
    void on_Button_space_clicked();
    void on_Button_backspace_clicked();
    void on_Button_Special_clicked();
    void on_Button_Cancel_clicked();
    void on_Button_Confirm_clicked();

    void on_Button_q_clicked();
    void on_Button_w_clicked();
    void on_Button_e_clicked();
    void on_Button_r_clicked();
    void on_Button_t_clicked();
    void on_Button_y_clicked();
    void on_Button_u_clicked();
    void on_Button_i_clicked();
    void on_Button_o_clicked();
    void on_Button_p_clicked();

    void on_Button_a_clicked();
    void on_Button_s_clicked();
    void on_Button_d_clicked();
    void on_Button_f_clicked();
    void on_Button_g_clicked();
    void on_Button_h_clicked();
    void on_Button_j_clicked();
    void on_Button_k_clicked();
    void on_Button_l_clicked();

    void on_Button_z_clicked();
    void on_Button_x_clicked();
    void on_Button_c_clicked();
    void on_Button_v_clicked();
    void on_Button_b_clicked();
    void on_Button_n_clicked();
    void on_Button_m_clicked();

    void on_Button_dot_clicked();

private:
    Ui::keyboard *ui;
    bool init = false;
    bool lower_case = true;
    bool special = false;
};

#endif // KEYBOARD_H
