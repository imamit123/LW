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
/*
$line_item_num = $row->commerce_line_item_field_data_commerce_line_items_line_item_;
  $result = db_select('eck_subscription', 'es');
  $result->fields('es', array('qty'));
  $result->condition('line_item_id', $line_item_num, 'LIKE');
  $result->range(0, 1);
  $result1 = $result->execute()->fetchAssoc();
  $output = $result1['qty'] . " months";
*/
  $product_id = $row->_field_data['commerce_line_item_field_data_commerce_line_items_line_item_']['entity']->commerce_product['und'][0]['product_id'];
  $query = db_select('taxonomy_term_data', 'td');
  $query->join('field_data_field_class_user', 'fs', ' td.tid = fs.field_class_user_tid');
  $res = $query->fields('td', array('name'))
	->condition('fs.entity_id', $product_id)
	->condition("fs.bundle", "package")
	->range(0, 1)
	->execute()
	->fetchAssoc();
	
  $output = $res['name'];
  print $output; 
  
?>
