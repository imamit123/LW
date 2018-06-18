<?php
/**
 * @file
 * offer_code_display_cck.features.inc
 */

/**
 * Implements hook_node_info().
 */
function offer_code_display_cck_node_info() {
  $items = array(
    'offer_code_display' => array(
      'name' => t('Offer Code Display'),
      'base' => 'node_content',
      'description' => t('Display Offer Code On Home Page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
