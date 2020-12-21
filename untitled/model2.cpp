#include "model2.h"

Model2::Model2()
{

}

Qt::ItemFlags  Model2::flags(const QModelIndex & index) const{
  // Column 0 always records the mark variable (our boolean).
  if (index.column() == 1) {
    // Make sure that this item is checkable.
    return QSqlTableModel::flags(index) | Qt::ItemIsUserCheckable;
  }
  // Default behaviour in all other cases.
  return QSqlTableModel::flags(index);
}

QVariant Model2::data(const QModelIndex &index, int role) const
{
  if (index.column() == 1)
    { // This is always the column with the boolean variable
      if (role == Qt::CheckStateRole)
    { // Only do the below when we are setting the checkbox.
      // We can simply fetch the value from the current index
      int checked = QSqlTableModel::data(index).toInt();
      // If checked == 1, then it evaluates to true in the if-statement below.
      // If checked == 0, the statement evaluates to false.
      if (checked)
        {
          return Qt::Checked;
        }
      else
        {
          return Qt::Unchecked;
        }
    }
      else
    {
      /*
        We return an empty variant in all other cases. This is to prevent, for example,
        that we also see a '0' or '1' in the same column.
      */
      return QVariant();
    }
      // Only do the below if we want to fetch a tool tip.
    }
  /*else if (role == Qt::ToolTipRole)
    {
      // I just want the tool tip to show the data in the column.
      const QString original = QSqlTableModel::data(index, Qt::DisplayRole).toString();
     // QString toolTip = breakString(original); // breakString() breaks the text in smaller lines.
      QString toolTip;
      return toolTip;
      // I want to make sure that broken lines have a space between them.
    }
  else if (role == Qt::DisplayRole)
    {
      const QString original = QSqlTableModel::data(index, Qt::DisplayRole).toString();
   //   QString shownText = fixBreakLines(original);
      QString shownText;
      return shownText;
    }*/
  else
    {
      /*
     In all other cases, we want the default behaviour of this function.
     This can be done easily by returning the default version of the function,
     rather than the re-implemented version we have here.
      */
      return QSqlTableModel::data(index, role);
    }
  return QVariant(); // This prevents a compiler warning.
}

bool Model2::setData(const QModelIndex & index, const QVariant & value, int role)
{
  /*
     Let's check whether the selected column is the column with our boolean variable
     (always column 7), and whether we are trying to set data under the
     Qt::CheckStateRole.
  */
  if (index.column() == 1 && role == Qt::CheckStateRole)
    {
      // Writing the data when the check box is set to checked.
      if (value == Qt::Checked)
    {
      // Let's write the new value
      return setData(index, 1);
      // Writing the data when the check box is set to unchecked
    }
      else if (value == Qt::Unchecked)
    {
      // Let's write the new value
      return setData(index, 0);
    }
    }
  // In all other situations revert to default behaviour.
  return QSqlTableModel::setData(index, value, role);
}

