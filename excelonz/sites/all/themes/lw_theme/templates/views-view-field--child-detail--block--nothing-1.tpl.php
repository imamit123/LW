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
<?php //print $output;
//print'<pre>';print_r($row);die();
//$output .= $row->_field_data['pid']['entity']->field_city['und'][0]['taxonomy_term']->name;
$class =$row->field_field_class_user_1[0]['rendered']['#title'];
$section =$row->field_field_class_user_1[1]['rendered']['#title'];
//print "<div class=user-span><city>City</span><span class=field-content>".$output ."</span></div>";
//print "<div class=user-class><span>Class</span><span class=field-content>".$class ."</span></div>";
print "<div class=user-section><span>Section</span><span class=field-contents>".$section ."</span></div>";


?>
