<?php
/* Some common code for course content type. */

// Implements autocomplete for course node content type - course title.
//
// Look at the corresponding javascript. For convenience, we add the course
// number to the course title here.  We strip that out in javascript on 
// selection from the drop-down autoselect list.
function _unh_d1_drupal_title_autocomplete($string) {
  $matches = array();

  $program_area = unh_d1_drupal_settings_program_area();
  $courses = unh_d1_client_searchCourse_keyword($string, $program_area);
  
  // Add '(course number)' to autocomplete display.  This will be stripped out
  // in the corresponding javascript.
  if (!empty($courses)) {
    foreach ($courses as $course) {
      $matches[$course['courseNumber']] = $course['name'] . '  (' . $course['courseNumber'] . ')';
    }
    if (!empty($matches)) {
      asort($matches, SORT_REGULAR);
    }
  }

  // return for JS
  drupal_json_output($matches);
}

// 
// Implements autocomplete for course node content type - course title.
//
function _unh_d1_drupal_certificate_title_autocomplete($string) {
  $matches = array();

  $program_area = unh_d1_drupal_settings_program_area();
  $information_level = 'long';
  $certificates = unh_d1_client_getCertificates($program_area, $information_level);
  // Add '(course number)' to autocomplete display.  This will be stripped out
  // in the corresponding javascript.
  if (!empty($certificates)) {
    foreach ($certificates as $certificate) {
      $matches[$certificate['code']] = $certificate['name'] . '  (' . $certificate['code'] . ')';
      // $matches[$certificate['code']] = $certificate['name'];
    }
    if (!empty($matches)) {
      asort($matches, SORT_REGULAR);
    }
  }

  // return for JS
  drupal_json_output($matches);
}

