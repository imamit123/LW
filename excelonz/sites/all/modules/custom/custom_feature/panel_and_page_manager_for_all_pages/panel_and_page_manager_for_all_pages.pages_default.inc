<?php
/**
 * @file
 * panel_and_page_manager_for_all_pages.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function panel_and_page_manager_for_all_pages_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'home_page';
  $page->task = 'page';
  $page->admin_title = 'Home Page';
  $page->admin_description = '';
  $page->path = '<front>';
  $page->access = array();
  $page->menu = array(
    'type' => 'none',
    'title' => '',
    'weight' => '0',
    'name' => 'navigation',
    'parent' => array(
      'type' => 'none',
      'title' => '',
      'weight' => 0,
      'name' => 'navigation',
    ),
  );
  $page->arguments = array();
  $page->conf = array();
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_home_page_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'home_page';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Landing page',
    'no_blocks' => FALSE,
    'pipeline' => 'ipe',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'flexible:home_page_new_layout';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'two_brick_top' => NULL,
      'two_brick_left_above' => NULL,
      'two_brick_right_above' => NULL,
      'two_brick_middle' => NULL,
      'two_brick_left_below' => NULL,
      'two_brick_right_below' => NULL,
      'two_brick_bottom' => NULL,
      'center' => NULL,
      'slideshow_1' => NULL,
      'ticker' => NULL,
      'class_dummy' => NULL,
      'class_section' => NULL,
      'excelonz_block' => NULL,
      'why_excelonz_test' => NULL,
      'join_excelonz_block' => NULL,
      'join_excelonz_free_block' => NULL,
      'join_excelonz_free' => NULL,
      'excelonz_block_new_design' => NULL,
      'excelonz_block_last_block' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-1';
    $pane->panel = 'center';
    $pane->type = 'block';
    $pane->subtype = 'block-49';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $display->content['new-1'] = $pane;
    $display->panels['center'][0] = 'new-1';
    $pane = new stdClass();
    $pane->pid = 'new-2';
    $pane->panel = 'center';
    $pane->type = 'block';
    $pane->subtype = 'lw_worksheet-try_question_and_worksheet';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $display->content['new-2'] = $pane;
    $display->panels['center'][1] = 'new-2';
    $pane = new stdClass();
    $pane->pid = 'new-3';
    $pane->panel = 'class_dummy';
    $pane->type = 'block';
    $pane->subtype = 'block-40';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => 'Home Page Test Paper Block',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $display->content['new-3'] = $pane;
    $display->panels['class_dummy'][0] = 'new-3';
    $pane = new stdClass();
    $pane->pid = 'new-4';
    $pane->panel = 'class_dummy';
    $pane->type = 'block';
    $pane->subtype = 'block-50';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $display->content['new-4'] = $pane;
    $display->panels['class_dummy'][1] = 'new-4';
    $pane = new stdClass();
    $pane->pid = 'new-5';
    $pane->panel = 'class_section';
    $pane->type = 'block';
    $pane->subtype = 'block-41';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => 'Home Page Genius page',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $display->content['new-5'] = $pane;
    $display->panels['class_section'][0] = 'new-5';
    $pane = new stdClass();
    $pane->pid = 'new-6';
    $pane->panel = 'excelonz_block';
    $pane->type = 'block';
    $pane->subtype = 'block-44';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => 'Home Page Subject and Topic Text Block',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $display->content['new-6'] = $pane;
    $display->panels['excelonz_block'][0] = 'new-6';
    $pane = new stdClass();
    $pane->pid = 'new-7';
    $pane->panel = 'excelonz_block_last_block';
    $pane->type = 'block';
    $pane->subtype = 'block-43';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => 'Home Page Get Started Here',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $display->content['new-7'] = $pane;
    $display->panels['excelonz_block_last_block'][0] = 'new-7';
    $pane = new stdClass();
    $pane->pid = 'new-8';
    $pane->panel = 'excelonz_block_new_design';
    $pane->type = 'block';
    $pane->subtype = 'block-42';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => 'Home Page Why Excelonz Block',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $display->content['new-8'] = $pane;
    $display->panels['excelonz_block_new_design'][0] = 'new-8';
    $pane = new stdClass();
    $pane->pid = 'new-9';
    $pane->panel = 'join_excelonz_block';
    $pane->type = 'block';
    $pane->subtype = 'lw_worksheet-homepage_subject_practice';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $display->content['new-9'] = $pane;
    $display->panels['join_excelonz_block'][0] = 'new-9';
    $pane = new stdClass();
    $pane->pid = 'new-10';
    $pane->panel = 'join_excelonz_block';
    $pane->type = 'block';
    $pane->subtype = 'block-46';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => 'Home Page Testimonial 2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $display->content['new-10'] = $pane;
    $display->panels['join_excelonz_block'][1] = 'new-10';
    $pane = new stdClass();
    $pane->pid = 'new-11';
    $pane->panel = 'slideshow_1';
    $pane->type = 'views';
    $pane->subtype = '_home_slideshow_field_collection';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '6',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'block_1',
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $display->content['new-11'] = $pane;
    $display->panels['slideshow_1'][0] = 'new-11';
    $pane = new stdClass();
    $pane->pid = 'new-12';
    $pane->panel = 'ticker';
    $pane->type = 'views';
    $pane->subtype = 'all_page_offer_code_ticker';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '3',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'block_1',
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $display->content['new-12'] = $pane;
    $display->panels['ticker'][0] = 'new-12';
    $pane = new stdClass();
    $pane->pid = 'new-13';
    $pane->panel = 'why_excelonz_test';
    $pane->type = 'block';
    $pane->subtype = 'block-45';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => 'Home Page Testimonial 1',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $display->content['new-13'] = $pane;
    $display->panels['why_excelonz_test'][0] = 'new-13';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = 'new-11';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['home_page'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'why_excelonz';
  $page->task = 'page';
  $page->admin_title = 'Why Excelonz';
  $page->admin_description = '';
  $page->path = 'why-excelonz';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_why_excelonz_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'why_excelonz';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'flexible:tour_page_layout';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
      'tour_excelonz_slider' => NULL,
      'tour_excelonz_self_practice' => NULL,
      'tour_practice_your_own_way' => NULL,
      'tour_get_better_prepared' => NULL,
      'tour_performance_progress' => NULL,
      'tour_challenges_motivation_fun' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-14';
    $pane->panel = 'tour_challenges_motivation_fun';
    $pane->type = 'block';
    $pane->subtype = 'block-59';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $display->content['new-14'] = $pane;
    $display->panels['tour_challenges_motivation_fun'][0] = 'new-14';
    $pane = new stdClass();
    $pane->pid = 'new-15';
    $pane->panel = 'tour_excelonz_self_practice';
    $pane->type = 'block';
    $pane->subtype = 'block-55';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $display->content['new-15'] = $pane;
    $display->panels['tour_excelonz_self_practice'][0] = 'new-15';
    $pane = new stdClass();
    $pane->pid = 'new-16';
    $pane->panel = 'tour_excelonz_slider';
    $pane->type = 'block';
    $pane->subtype = 'block-54';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $display->content['new-16'] = $pane;
    $display->panels['tour_excelonz_slider'][0] = 'new-16';
    $pane = new stdClass();
    $pane->pid = 'new-17';
    $pane->panel = 'tour_get_better_prepared';
    $pane->type = 'block';
    $pane->subtype = 'block-57';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $display->content['new-17'] = $pane;
    $display->panels['tour_get_better_prepared'][0] = 'new-17';
    $pane = new stdClass();
    $pane->pid = 'new-18';
    $pane->panel = 'tour_performance_progress';
    $pane->type = 'block';
    $pane->subtype = 'block-58';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $display->content['new-18'] = $pane;
    $display->panels['tour_performance_progress'][0] = 'new-18';
    $pane = new stdClass();
    $pane->pid = 'new-19';
    $pane->panel = 'tour_practice_your_own_way';
    $pane->type = 'block';
    $pane->subtype = 'block-56';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $display->content['new-19'] = $pane;
    $display->panels['tour_practice_your_own_way'][0] = 'new-19';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['why_excelonz'] = $page;

  return $pages;

}
