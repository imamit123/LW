<?php
/**
 * @file
 * cck_extra_fields.features.inc
 */

/**
 * Implements hook_node_info().
 */
function cck_extra_fields_node_info() {
  $items = array(
    'fib' => array(
      'name' => t('Fill in the blanks type questions'),
      'base' => 'node_content',
      'description' => t('This Content type stores FIB Questions, Missing letters in block Questions, Suffixes and prefixes Questions, Comparatives Questions, Complete the series Questions, 
Puzzle Questions.'),
      'has_title' => '1',
      'title_label' => t('Question Title'),
      'help' => '',
    ),
    'mcq' => array(
      'name' => t('Multiple choice type questions'),
      'base' => 'node_content',
      'description' => t('This content type includes MCQ type questions'),
      'has_title' => '1',
      'title_label' => t('Question Title'),
      'help' => '',
    ),
    'true_and_false' => array(
      'name' => t('True and False'),
      'base' => 'node_content',
      'description' => t('This content type includes True/False type questions.'),
      'has_title' => '1',
      'title_label' => t('Question Title'),
      'help' => '',
    ),
  );
  return $items;
}
