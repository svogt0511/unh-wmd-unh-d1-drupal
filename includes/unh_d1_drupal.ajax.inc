<?php

/**
 * @file
 *
 * @todo: Update this docblock.
 * @todo: make sure we get full output on other than 'short' informationLevel
 *
 * Functions implementing backend for ajax calls.  (Mostly section status.)
 */

/**
 *
 * Implements the callback functions to render section RR with fresh statuses.
 *
 */

function unh_d1_drupal_ajax_get_section_status($nid, $program_area, $course_code, $conf) {
  $ret = '';
  $conf = $_POST;
  
  if (!empty($nid) && !empty($program_area) && !empty($course_code)) {
    $node = node_load($nid);
    $course = unh_d1_client_searchCourse_courseCode($course_code, array($program_area), 'full');
    $sections_ret = unh_d1_client_searchCourseSections($course_code, array($program_area), 'full');
    
    $sections = [];
    // Only use current course sections.
    foreach($sections_ret as $section) {
      if (!unh_d1_client_sectionIsNoLongerAvailable($section)) {
        $sections[] = $section;
      }
    }
  
    $ret = theme('unh_d1_drupal__d1__course_sections_pane', array('course_nid' => $nid, 'course' => $course, 'sections' => $sections, 'config' => $conf));
  }
  
  return $ret;
}

function unh_d1_drupal_ajax_get_section_status_callback($page_callback_result) {
  $content = $page_callback_result;
  $html = '<div id="ajax-section-status">' . $content . '</div>';

  print $html;
}
