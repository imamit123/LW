<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */
?>
<?php

  $months = array();
  $months[3] = array(1250, 1750, 2500, 3250, 4000);
  $months[6] = array(2500, 3500, 5000, 6500, 8000);
  $months[12] = array(5000, 7000, 10000, 13000, 16000);

 $line_item_num = $row->commerce_line_item_field_data_commerce_line_items_line_item_;
  $result = db_select('eck_subscription', 'es');
  $result->fields('es');
  $result->condition('line_item_id', $line_item_num, 'LIKE');
  $result->range(0, 1);
  $result1 = $result->execute()->fetchAssoc();
  //$output = $months[$result1['qty']][0];
  $_SESSION['orig_amount'] += $output;
  print $output;
?>


