<?php

/**
 * @file
 *
 * @todo: Update this docblock.
 * @todo: make sure we get full output on other than 'short' informationLevel
 *
 * Functions for administrative functionality
 */
 

/*
 *
 * ADMIN REPORT: GET LIST OF COURSES VISIBLE IN D1 BUT HAVE NO CORRESPONDING DRUPAL COURSE NODE.
 *
 */
function unh_d1_drupal_reports_orphan_d1_courses() {

  // '' gets all courses.
  // https://learnforlife.unh.edu/search/publicCourseSearchDetails.do?method=load&courseId=22520
  //list($total, $courses) = _d1pdt_search_by_text('', D1PDT_EXCLUDE_NON_ORPHANS);
  list($grand_total, $courses) = unh_d1_drupal_search_by_text('all', UNH_D1_DRUPAL_EXCLUDE_NON_ORPHANS);

/*
  for ($i = 0; $i < $total; $i++) {
    if (!empty(unh_d1_drupal_get_course_node($courses[$i]))) {
      unset($courses[$i]);
    } else {
      $courses[$i]['courseURL'] = unh_d1_client_get_d1_url($courses[$i]);
    }
  }
  */
  
  // Get rid of non-d1 courses.
  foreach($courses as $key=>$course) {
    if (empty(unh_d1_drupal_get_course_node($course))) {
      $courses[$key]['courseURL'] = unh_d1_client_get_d1_url($course);
    } else {
      unset($courses[$key]);
    }
  }

  $total = count($courses);

  $html = '<div style="margin-bottom: 15px;">This report lists all remote DestinyOne (D1) courses that have no corresponding local Drupal course nodes.  (The D1 courses are "orphans".)</div>';

  $html .= '<div>Total number of visible D1 courses = ' . ($grand_total - $total) . '</div>';
  $html .= '<div style="margin-bottom: 15px;">Total number of orphan D1 courses = ' . $total . '</div>';
  $html .= '<div style="margin-bottom: 10px;font-weight: bold">ORPHAN D1 COURSE LIST:</div>';

  $html .= unh_d1_drupal_admin_get_simpleCourseListBlock_markup($courses);

  $html .= '<div style="margin: 15px 0 15px 0;">(*)The D1 modules rely upon the correspondence between course nodes in Drupal (local) and courses in DestinyOne (remote).  This correspondence is established by the "course code" field in a local Drupal course node. A Drupal course node that has corresponding D1 course data must have a "course code" that explicitly identifies that D1 course.  Courses in Drupal (local) or D1 (remote) that are not connected by a course code are "orphans".</div>';

    $html .= '<div style="margin-bottom: 15px;">(**)To establish this connection, go to admin=>content=>add content=>course. Start typing in a course title in the title field, and select the desired D1 course from the autocomplete drop down list. This will cause the course code field to be automatically filled in, identifying the corresponding D1 course data.</div>';

  return $html;
}


/*
 *
 * DISPLAY: CONTENT PANE (In course page, testimonials tab, the signature - global php
 *  in views.)
 *
 *
 */

//GET MARKUP FOR SEARCH results course list

function unh_d1_drupal_admin_get_simpleCourseListBlock_markup($courses) {

  if (empty($courses)) {
    return '';
  }

  uasort($courses, function ($a, $b) { return strnatcasecmp(unh_d1_client_getcourseName($a), unh_d1_client_getcourseName($b)); });

  $str = '
<ul class="list__chevron course-list">';

  foreach ($courses as $course) {

    $str .= '
  <li class="course-row">';

    // courseURL was added by us, not D1.
    $str .= '<a href="' . $course['courseURL']  . '">' . unh_d1_client_getcourseName($course) . ' (' . unh_d1_client_getcourseNumber($course) .')</a>';

    $str .= '
  </li>';
  }

  $str .= '
</ul>';

  return $str;
}

