<?php
/**
 * @file
 * add_new_fields_in_feed_for_cck.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function add_new_fields_in_feed_for_cck_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'fib_import';
  $feeds_importer->config = array(
    'name' => 'FIB import',
    'description' => 'this imports the FIB\'s from csv files',
    'fetcher' => array(
      'plugin_key' => 'FeedsFileFetcher',
      'config' => array(
        'allowed_extensions' => 'txt csv tsv xml opml',
        'direct' => 0,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsCSVParser',
      'config' => array(
        'delimiter' => ',',
        'no_headers' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'content_type' => 'fib',
        'expire' => '-1',
        'author' => '1',
        'mappings' => array(
          0 => array(
            'source' => 'title',
            'target' => 'title',
            'unique' => 0,
          ),
          1 => array(
            'source' => 'class',
            'target' => 'field_class',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'subject',
            'target' => 'field_subjects',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'question level',
            'target' => 'field_question_level',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'question text',
            'target' => 'field_question_text',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'correct word',
            'target' => 'field_correct_word',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'guid',
            'target' => 'guid',
            'unique' => 1,
          ),
          7 => array(
            'source' => 'skills',
            'target' => 'field_skills',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'submitted by',
            'target' => 'field_submitted_by',
            'unique' => FALSE,
          ),
          9 => array(
            'source' => 'reviewed by',
            'target' => 'field_reviewed_by',
            'unique' => FALSE,
          ),
          10 => array(
            'source' => 'question image',
            'target' => 'field_question_image',
            'unique' => FALSE,
          ),
          11 => array(
            'source' => 'explanation',
            'target' => 'field_question_description',
            'unique' => FALSE,
          ),
          12 => array(
            'source' => 'answer explanation image',
            'target' => 'field_answer_explanation_img',
            'unique' => FALSE,
          ),
          13 => array(
            'source' => 'FIB for Anonymous',
            'target' => 'field_fib_for_anonymous',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '1',
        'input_format' => 'plain_text',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['fib_import'] = $feeds_importer;

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'match_the_following';
  $feeds_importer->config = array(
    'name' => 'match the following',
    'description' => 'importer for the match the following content type',
    'fetcher' => array(
      'plugin_key' => 'FeedsFileFetcher',
      'config' => array(
        'allowed_extensions' => 'txt csv tsv xml opml',
        'direct' => 0,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsCSVParser',
      'config' => array(
        'delimiter' => ',',
        'no_headers' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'content_type' => 'match_the_following',
        'expire' => '-1',
        'author' => 0,
        'mappings' => array(
          0 => array(
            'source' => 'guid',
            'target' => 'guid',
            'unique' => 1,
          ),
          1 => array(
            'source' => 'title',
            'target' => 'title',
            'unique' => 0,
          ),
          2 => array(
            'source' => 'class',
            'target' => 'field_class',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'subject and topics',
            'target' => 'field_subjects',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'q-scale',
            'target' => 'field_question_level',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'skills',
            'target' => 'field_skills',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'question text',
            'target' => 'field_question_text',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'answer explaination',
            'target' => 'field_question_description',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'correct matched word:given word',
            'target' => 'field_correct_match_word:field_given_word',
            'unique' => FALSE,
          ),
          9 => array(
            'source' => 'correct matched word:correct match',
            'target' => 'field_correct_match_word:field_correct_match',
            'unique' => FALSE,
          ),
          10 => array(
            'source' => 'submitted by',
            'target' => 'field_submitted_by',
            'unique' => FALSE,
          ),
          11 => array(
            'source' => 'reviewed by',
            'target' => 'field_reviewed_by',
            'unique' => FALSE,
          ),
          12 => array(
            'source' => 'correctimg',
            'target' => 'field_correct_match_word:field_correct_image',
            'unique' => FALSE,
          ),
          13 => array(
            'source' => 'givenimg',
            'target' => 'field_correct_match_word:field_image_option',
            'unique' => FALSE,
          ),
          14 => array(
            'source' => 'answer explanation image',
            'target' => 'field_answer_explanation_img',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '1',
        'input_format' => 'plain_text',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['match_the_following'] = $feeds_importer;

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'true_and_false';
  $feeds_importer->config = array(
    'name' => 'True and false',
    'description' => '',
    'fetcher' => array(
      'plugin_key' => 'FeedsFileFetcher',
      'config' => array(
        'allowed_extensions' => 'txt csv tsv xml opml',
        'direct' => FALSE,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsCSVParser',
      'config' => array(
        'delimiter' => ',',
        'no_headers' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'content_type' => 'true_and_false',
        'expire' => '-1',
        'author' => '1',
        'mappings' => array(
          0 => array(
            'source' => 'guid',
            'target' => 'guid',
            'unique' => 1,
          ),
          1 => array(
            'source' => 'question title',
            'target' => 'title',
            'unique' => 0,
          ),
          2 => array(
            'source' => 'class',
            'target' => 'field_class',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'subject and topics',
            'target' => 'field_subjects',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'q-scale',
            'target' => 'field_question_level',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'question text',
            'target' => 'field_question_text',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'question image',
            'target' => 'field_question_image',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'answer choices: Text Based Option',
            'target' => 'field_answer_choices:field_option_1',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'answer choices: Image Based Option',
            'target' => 'field_answer_choices:field_image_option',
            'unique' => FALSE,
          ),
          9 => array(
            'source' => 'answer choices:option',
            'target' => 'field_answer_choices:field_correct_answer',
            'unique' => FALSE,
          ),
          10 => array(
            'source' => 'skills',
            'target' => 'field_skills',
            'unique' => FALSE,
          ),
          11 => array(
            'source' => 'answer explanation',
            'target' => 'field_question_description',
            'unique' => FALSE,
          ),
          12 => array(
            'source' => 'submitted by',
            'target' => 'field_submitted_by',
            'unique' => FALSE,
          ),
          13 => array(
            'source' => 'reviewed by',
            'target' => 'field_reviewed_by',
            'unique' => FALSE,
          ),
          14 => array(
            'source' => 'answer explanation image',
            'target' => 'field_answer_explanation_img',
            'unique' => FALSE,
          ),
          15 => array(
            'source' => 'True and False for Anonymous',
            'target' => 'field_true_and_false_for_anonymo',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'input_format' => 'plain_text',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['true_and_false'] = $feeds_importer;

  return $export;
}
