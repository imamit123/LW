<?php
/**
 * @file
 * image_style.features.inc
 */

/**
 * Implements hook_image_default_styles().
 */
function image_style_image_default_styles() {
  $styles = array();

  // Exported image style: slideshow_image_all_pages.
  $styles['slideshow_image_all_pages'] = array(
    'name' => 'slideshow_image_all_pages',
    'effects' => array(
      28 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 678,
          'height' => 407,
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      29 => array(
        'label' => 'Resize',
        'help' => 'Resizing will make images an exact set of dimensions. This may cause images to be stretched or shrunk disproportionately.',
        'effect callback' => 'image_resize_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_resize',
        'data' => array(
          'width' => 678,
          'height' => 407,
        ),
        'weight' => 2,
      ),
    ),
  );

  return $styles;
}
