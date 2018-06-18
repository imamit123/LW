<?php
/**
 * @file
 * panel_and_page_manager_for_all_pages.layouts.inc
 */

/**
 * Implements hook_default_panels_layout().
 */
function panel_and_page_manager_for_all_pages_default_panels_layout() {
  $export = array();

  $layout = new stdClass();
  $layout->disabled = FALSE; /* Edit this to true to make a default layout disabled initially */
  $layout->api_version = 1;
  $layout->name = 'home_page_new_layout';
  $layout->admin_title = 'Home Page New Layout';
  $layout->admin_description = '';
  $layout->category = 'Miscellaneous';
  $layout->plugin = 'flexible';
  $layout->settings = array(
    'items' => array(
      'canvas' => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          0 => 'main',
        ),
        'parent' => NULL,
        'class' => '',
        'column_class' => '',
        'row_class' => '',
        'region_class' => '',
        'no_scale' => FALSE,
        'fixed_width' => '',
        'column_separation' => '0.5em',
        'region_separation' => '0.5em',
        'row_separation' => '0.5em',
      ),
      'main' => array(
        'type' => 'column',
        'width' => 100,
        'width_type' => '%',
        'children' => array(
          0 => 1,
          1 => 'main-row',
          2 => 2,
          3 => 3,
          4 => 4,
          5 => 5,
          6 => 6,
          7 => 7,
          8 => 8,
        ),
        'parent' => 'canvas',
      ),
      'main-row' => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'slideshow_1',
          1 => 'center',
        ),
        'parent' => 'main',
      ),
      'center' => array(
        'type' => 'region',
        'title' => 'Center',
        'width' => '31.771355943541376',
        'width_type' => '%',
        'parent' => 'main-row',
      ),
      1 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(),
        'parent' => 'main',
        'class' => 'slideshow',
      ),
      'slideshow_1' => array(
        'type' => 'region',
        'title' => 'slideshow-1',
        'width' => '68.22864405645862',
        'width_type' => '%',
        'parent' => 'main-row',
        'class' => '',
      ),
      2 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'ticker',
        ),
        'parent' => 'main',
        'class' => 'ticker',
      ),
      'ticker' => array(
        'type' => 'region',
        'title' => 'ticker',
        'width' => 100,
        'width_type' => '%',
        'parent' => '2',
        'class' => '',
      ),
      3 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'class_section',
          1 => 'class_dummy',
        ),
        'parent' => 'main',
        'class' => 'class-dummy-content',
      ),
      'class_dummy' => array(
        'type' => 'region',
        'title' => 'class-dummy',
        'width' => '31.60049808865502',
        'width_type' => '%',
        'parent' => '3',
        'class' => '',
      ),
      'class_section' => array(
        'type' => 'region',
        'title' => 'class-section',
        'width' => '68.39950191134498',
        'width_type' => '%',
        'parent' => '3',
        'class' => '',
      ),
      4 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'excelonz_block',
        ),
        'parent' => 'main',
        'class' => 'why-excelonz',
      ),
      'excelonz_block' => array(
        'type' => 'region',
        'title' => 'excelonz-block',
        'width' => 100,
        'width_type' => '%',
        'parent' => '4',
        'class' => '',
      ),
      5 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'join_excelonz_block',
          1 => 'why_excelonz_test',
        ),
        'parent' => 'main',
        'class' => 'why-excelonz',
      ),
      'why_excelonz_test' => array(
        'type' => 'region',
        'title' => 'why-excelonz-test',
        'width' => '31.85747522190851',
        'width_type' => '%',
        'parent' => '5',
        'class' => '',
      ),
      'join_excelonz_block' => array(
        'type' => 'region',
        'title' => 'join-excelonz-block',
        'width' => '68.1425247780915',
        'width_type' => '%',
        'parent' => '5',
        'class' => '',
      ),
      6 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'join_excelonz_free',
          1 => 'join_excelonz_free_block',
        ),
        'parent' => 'main',
        'class' => 'join-excelonz-free',
      ),
      'join_excelonz_free_block' => array(
        'type' => 'region',
        'title' => 'join-excelonz-free-block',
        'width' => '31.627037091963683',
        'width_type' => '%',
        'parent' => '6',
        'class' => '',
      ),
      'join_excelonz_free' => array(
        'type' => 'region',
        'title' => 'join-excelonz-free',
        'width' => '68.37296290803631',
        'width_type' => '%',
        'parent' => '6',
        'class' => '',
      ),
      7 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'excelonz_block_new_design',
        ),
        'parent' => 'main',
        'class' => 'excelonz_block_new_design',
      ),
      'excelonz_block_new_design' => array(
        'type' => 'region',
        'title' => 'excelonz_block_new_design',
        'width' => 100,
        'width_type' => '%',
        'parent' => '2',
        'class' => '',
      ),
      8 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'excelonz_block_last_block',
        ),
        'parent' => 'main',
        'class' => 'excelonz_block_last_block',
      ),
      'excelonz_block_last_block' => array(
        'type' => 'region',
        'title' => 'excelonz_block_last_block',
        'width' => 100,
        'width_type' => '%',
        'parent' => '2',
        'class' => '',
      ),
    ),
  );
  $export['home_page_new_layout'] = $layout;

  $layout = new stdClass();
  $layout->disabled = FALSE; /* Edit this to true to make a default layout disabled initially */
  $layout->api_version = 1;
  $layout->name = 'tour_page_layout';
  $layout->admin_title = 'Tour Page Layout';
  $layout->admin_description = '';
  $layout->category = 'Tour Page Layout';
  $layout->plugin = 'flexible';
  $layout->settings = array(
    'items' => array(
      'canvas' => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          0 => 'main',
        ),
        'parent' => NULL,
      ),
      'main' => array(
        'type' => 'column',
        'width' => 100,
        'width_type' => '%',
        'children' => array(
          0 => 'main-row',
          1 => 1,
          2 => 2,
          3 => 3,
          4 => 4,
          5 => 5,
          6 => 6,
        ),
        'parent' => 'canvas',
      ),
      'main-row' => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'center',
        ),
        'parent' => 'main',
      ),
      'center' => array(
        'type' => 'region',
        'title' => 'Center',
        'width' => 100,
        'width_type' => '%',
        'parent' => 'main-row',
      ),
      1 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'tour_excelonz_slider',
        ),
        'parent' => 'main',
        'class' => 'tour-excelonz-slider',
      ),
      'tour_excelonz_slider' => array(
        'type' => 'region',
        'title' => 'Tour-excelonz-slider',
        'width' => 100,
        'width_type' => '%',
        'parent' => '1',
        'class' => '',
      ),
      2 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'tour_excelonz_self_practice',
        ),
        'parent' => 'main',
        'class' => 'Tour-excelonz-self-practice',
      ),
      'tour_excelonz_self_practice' => array(
        'type' => 'region',
        'title' => 'Tour-excelonz-self-practice',
        'width' => 100,
        'width_type' => '%',
        'parent' => '2',
        'class' => '',
      ),
      3 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'tour_practice_your_own_way',
        ),
        'parent' => 'main',
        'class' => 'Tour-practice-your-own-way',
      ),
      'tour_practice_your_own_way' => array(
        'type' => 'region',
        'title' => 'Tour-practice-your-own-way',
        'width' => 100,
        'width_type' => '%',
        'parent' => '3',
        'class' => '',
      ),
      4 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'tour_get_better_prepared',
        ),
        'parent' => 'main',
        'class' => 'Tour-get-better-prepared',
      ),
      'tour_get_better_prepared' => array(
        'type' => 'region',
        'title' => 'Tour-get-better-prepared',
        'width' => 100,
        'width_type' => '%',
        'parent' => '4',
        'class' => '',
      ),
      5 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'tour_performance_progress',
        ),
        'parent' => 'main',
        'class' => 'Tour-performance-progress',
      ),
      'tour_performance_progress' => array(
        'type' => 'region',
        'title' => 'Tour-performance-progress',
        'width' => 100,
        'width_type' => '%',
        'parent' => '5',
        'class' => '',
      ),
      6 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'tour_challenges_motivation_fun',
        ),
        'parent' => 'main',
        'class' => 'tour-challenges-motivation-fun',
      ),
      'tour_challenges_motivation_fun' => array(
        'type' => 'region',
        'title' => 'tour-challenges-motivation-fun',
        'width' => 100,
        'width_type' => '%',
        'parent' => '6',
        'class' => '',
      ),
    ),
  );
  $export['tour_page_layout'] = $layout;

  return $export;
}
