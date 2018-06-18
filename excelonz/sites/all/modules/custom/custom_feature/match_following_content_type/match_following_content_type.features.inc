<?php
/**
 * @file
 * match_following_content_type.features.inc
 */

/**
 * Implements hook_node_info().
 */
function match_following_content_type_node_info() {
  $items = array(
    'match_the_following' => array(
      'name' => t('Match The Following'),
      'base' => 'node_content',
      'description' => t('This content type stores match the following content'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
