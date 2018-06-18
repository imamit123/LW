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
  global $base_url;

echo "<pre>";print_r($row);

if ($row->eck_badges2_badge_name == "mastered") {
  print theme_image_style(array(
  'style_name' => 'badges_240_100',
  'path' => $row->_field_data[taxonomy_term_data_field_data_field_termid_tid][entity]->field_mastered_image[und][0][filename],
  ));
}
 if ($row->eck_badges2_badge_name == "covered") {

 print theme_image_style(array(
  'style_name' => 'badges_240_100',
  'path' => $row->_field_data[taxonomy_term_data_field_data_field_termid_tid][entity]->field_covered_image[und][0][filename],
  ));

}
?>

<?php
/* foreach ($node->field_user_status['und'] as $option){
    $options = entity_load("field_collection_item", array($option['value'], ));
    $user_id = $options[$option['value']]->field_users['und'][0]['uid'];
$result = db_query("SELECT mail FROM users WHERE uid = :uuid", array(':uuid' =>$options[$option['value']]->field_users['und'][0]['uid'))->fetchAll();
echo "<pre>";
print_r($result);die();

//echo "<pre>";print_r($options[$option['value']]->field_users['und'][0]['uid']);die();

}
*/


?>