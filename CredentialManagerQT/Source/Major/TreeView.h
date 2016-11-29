﻿#ifndef _bnb_Tree_View_H_
#define _bnb_Tree_View_H_

QT_BEGIN_NAMESPACE

class TreeView : public QTreeWidget
{
public:

	TreeView(QWidget * parent = nullptr);

	void InitCredential();
	void ClearCredential();
	void UpdateHeader();

	QTreeWidgetItem* AddPlatform(QTreeWidgetItem* parent, const bnb::platform_list::data_type& pp);
	QTreeWidgetItem* AddAccount(QTreeWidgetItem* parent, const bnb::account_list::data_type& pa);
	QTreeWidgetItem* AddProperty(QTreeWidgetItem* parent, const bnb::property_list::data_type& pp);

};

QT_END_NAMESPACE

#endif	// _bnb_Tree_View_H_
