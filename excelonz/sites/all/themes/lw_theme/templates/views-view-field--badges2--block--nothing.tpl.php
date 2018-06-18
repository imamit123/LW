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
 //echo "<pre>"; print_r($row);die();
?>

<?php
  global $base_url;
  global $user;
  $uid = $user->uid;
  //$user_fields = user_load($uid);
  //$profile2 = profile2_load_by_user($user->uid);

if ($row->eck_badges2_badge_name == "mastered") {
  print theme_image_style(array(
  'style_name' => 'badges_240_100',
  'path' => substr($row->_field_data[taxonomy_term_data_field_data_field_termid_tid][entity]->field_mastered_image[und][0][uri], 9),
  ));
}
 if ($row->eck_badges2_badge_name == "covered") {

 print theme_image_style(array(
  'style_name' => 'badges_240_100',
  'path' => substr($row->_field_data[taxonomy_term_data_field_data_field_termid_tid][entity]->field_covered_image[und][0][uri], 9),
  ));

}
?>
