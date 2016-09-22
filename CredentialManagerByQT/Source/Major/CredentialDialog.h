﻿#ifndef _bnb_View_Dialog_H_
#define _bnb_View_Dialog_H_

QT_BEGIN_NAMESPACE

class QLabel;
class QComboBox;
class QPushButton;
class QTableWidget;

class CredentialDialog : public QDialog
{
    struct ui_type
    {
    private:

        QLabel* _labPlatform;
        QLabel* _labAccount;

    public:

        QAction* m_actEdit;
        QAction* m_actUp;
        QAction* m_actDown;
        QAction* m_actAdd;
        QAction* m_actRemove;

        QComboBox* m_cboxPlatform;
        QComboBox* m_cboxAccount;

        QTableWidget* m_tabProperty;
        QPushButton* m_btnClose;

        void SetupUI(CredentialDialog* pView);
        void RetranslateUI(CredentialDialog* pView);
    };

public:

	CredentialDialog(bnb::Credential& src, QWidget * parent = nullptr);
	
private:

    void InitView();

    void UpdateAccount();
    void UpdateProperty();

    void OnChangedPlatform(const QString& strText);
    void OnChangedAccount(const QString& strText);
    void OnDoubleClickedProperty(int row, int cln);
    void OnTableContextMenu(const QPoint& pos);
    void OnClickedEdit();
    void OnClickedUp();
    void OnClickedDown();
    void OnClickedAdd();
    void OnClickedRemove();

    bool SetKey(const bnb::platform_type& pp, const bnb::account_type& pa, bnb::string_type& k1, const bnb::string_type& k2) override;

private:
	
    bnb::Credential& m_Credential;

    bnb::account_list* m_ptrCurAccount{ nullptr };
    bnb::property_list* m_ptrCurProperty{ nullptr };

    ui_type _ui;
};

QT_END_NAMESPACE

#endif  // _bnb_View_Dialog_H_