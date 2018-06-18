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

  $line_item_num = $row->commerce_line_item_field_data_commerce_line_items_line_item_;
  $result = db_select('eck_subscription', 'es');
  $result->join('taxonomy_term_data', 'td', ' td.tid = es.subject_tid');
  $result->fields('td', array('name'));
  $result->condition('line_item_id', $line_item_num, 'LIKE');
  $result->condition("es.worksheet_tid", '0');
  $result->range(0, 1);
  $result1 = $result->execute()->fetchAssoc();
  if(isset($result1['name'])){
   echo $output123 = $result1['name'];
 }
  $result_worksheet = db_select('eck_subscription', 'es');
  $result_worksheet->join('taxonomy_term_data', 'td', ' td.tid = es.subject_tid');
  $result_worksheet->fields('td', array('name'));
  $result_worksheet->condition('line_item_id', $line_item_num, 'LIKE');
  $result_worksheet->condition("es.worksheet_tid", '0','<>');
  $result_worksheet->range(0, 1);
  $result1_worksheet = $result_worksheet->execute()->fetchAssoc();
  if(isset($result1_worksheet['name'])){
       echo $output234 = $result1_worksheet['name'].' Worksheet';
}
 ?>