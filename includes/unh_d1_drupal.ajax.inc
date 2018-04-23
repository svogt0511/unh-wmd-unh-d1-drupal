<?php

/**
 * @file
 *
 * @todo: Update this docblock.
 * @todo: make sure we get full output on other than 'short' informationLevel
 *
 * Functions implementing backend for ajax calls.  (Mostly section status.)
 */

/******************************************************************************
 *
 * Calls to extract settings for this module.
 *
 ******************************************************************************/

/**
 * Returns the program area as set in this module's settings.
 */
function unh_d1_drupal_ajax_get_section_status($courseId, $sectionId) {
  ddl($courseId, 'GOT HERE - AJAX CALL HANDLER');
  ddl($sectionId, 'GOT HERE - AJAX CALL HANDLER');

  $ret = 'GOT HERE - AJAX CALL HANDLER';
  if (!empty($courseId) && !empty($sectionId)) {
    $ret .= ' for: ' . $courseId . ' / ' . $sectionId;
  }
  return $ret;
}

function unh_d1_drupal_ajax_get_section_status_callback($page_callback_result) {
  // Only render content and validates return
  $content = $page_callback_result;
  // $content = is_string($page_callback_result) ? $page_callback_result :   drupal_render($page_callback_result);
  $html = '<div id="ajax-section-status">' . $content . '/</div>';
  // $html = '' . drupal_get_css() . drupal_get_js() . '' . $content . '';
  print $html;
  // drupal_page_footer(); 
}
