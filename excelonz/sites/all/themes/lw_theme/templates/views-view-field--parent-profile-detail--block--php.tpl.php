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
global $user;
  global $base_path;
  $uid = '';
  $uid = $user->uid;
$op = $row->field_child_id;
$num = count($row->_field_data[uid][entity]->field_child_id['und']);
 $link_child = l("Add Child", "admin/people/p2rp-create/student");
 // if ($num < 3){
 //  $link_child = l("Add Child", "admin/people/p2rp-create/student");
 // }
 // else {
 //   $link_child = '<a onClick="javascript: alert(\'For adding more children, please buy our enterprise subscription\')">Add Child</a>';
 // }
 $output .= '<li class="addChild one" style="cursor:pointer"><a href="/user/'.$uid.'/edit">Edit My Profile</a></li>
 <li class="addChild" style="cursor:pointer">'.$link_child.'</li>';
echo $output;
?>