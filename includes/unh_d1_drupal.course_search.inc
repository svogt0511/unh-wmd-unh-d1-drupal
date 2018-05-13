<?php
/**********************************************************
 *
 * FORM: COMMON CODE FOR SEARCH CODE
 *
 **********************************************************/


/*
 *
 * BLOCK DEFINITIONS
 *
 */

/**
* Implementation of hook_block_info().
*/

function unh_d1_drupal_block_info()
{
    $blocks = array();

    $blocks['unh_d1_courseSearchByText_block'] = array(
        'info' => t(UNH_D1_DRUPAL_COURSESEARCHBYTEXT_BLOCKTITLE_DEFAULT),
        'title' => t(UNH_D1_DRUPAL_COURSESEARCHBYTEXT_BLOCKTITLE_DEFAULT),
    );

    $blocks['unh_d1_courseSearchBar_block'] = array(
        'info' => t(UNH_D1_DRUPAL_COURSESEARCHBAR_BLOCKTITLE_DEFAULT),
        'title' => t(UNH_D1_DRUPAL_COURSESEARCHBAR_BLOCKTITLE_DEFAULT),
    );

    return $blocks;
}


/**
* Implementation of hook_block_view().
*/
function unh_d1_drupal_block_view($delta = '')
{
    $block = array();

    switch ($delta) {
      case 'unh_d1_courseSearchByText_block' :
            $block['content'] = drupal_get_form('unh_d1_drupal_courseSearchByText');
            break;
      case 'unh_d1_courseSearchBar_block' :
        $block['content'] = array(
          '#prefix' => '',
          '#markup' => unh_d1_drupal_get_searchBarBlock_markup(),
          '#suffix' => ''
        );
        break;
    }

    return $block;
}


function unh_d1_drupal_block_configure($delta = '') {

  $form = array();
  if ($delta == 'unh_d1_courseSearchBar_block') {

    $form['unh_d1_drupal_courseSearchBar_label'] = array(
      '#type' => 'textfield',
      '#title' => t('Enter the keyword search label:'),
      '#default_value' => variable_get('unh_d1_drupal_courseSearchBar_label'),
      '#size' => 60,
    );

    $form['unh_d1_drupal_courseSearchBar_tab'] = array(
      '#type' => 'textfield',
      '#title' => t('Enter the keyword search tab label:'),
      '#default_value' => variable_get('unh_d1_drupal_courseSearchBar_tab'),
      '#size' => 60,
    );

    $form['unh_d1_drupal_courseSearchBar_phrase'] = array(
      '#type' => 'textfield',
      '#title' => t('Enter the keyword search phrase:'),
      '#default_value' => variable_get('unh_d1_drupal_courseSearchBar_phrase'),
      '#size' => 60,
    );

    $form['unh_d1_drupal_courseSearchBar_submit'] = array(
      '#type' => 'textfield',
      '#title' => t('Enter the keyword search submit button label:'),
      '#default_value' => variable_get('unh_d1_drupal_courseSearchBar_submit'),
      '#size' => 60,
    );

    $form['unh_d1_drupal_courseSearchBar_filters'] = array(
      '#type' => 'checkbox',
      '#title' => t('Check to turn on the keyword search filters:'),
      '#default_value' => variable_get('unh_d1_drupal_courseSearchBar_filters'),
    );
  }

  return $form;
}


function unh_d1_drupal_block_save($delta = '', $edit = array()) {

  if ($delta == 'unh_d1_courseSearchBar_block') {
    variable_set('unh_d1_drupal_courseSearchBar_label', $edit['unh_d1_drupal_courseSearchBar_label']);
    variable_set('unh_d1_drupal_courseSearchBar_tab', $edit['unh_d1_drupal_courseSearchBar_tab']);
    variable_set('unh_d1_drupal_courseSearchBar_phrase', $edit['unh_d1_drupal_courseSearchBar_phrase']);
    variable_set('unh_d1_drupal_courseSearchBar_submit', $edit['unh_d1_drupal_courseSearchBar_submit']);
    variable_set('unh_d1_drupal_courseSearchBar_filters', $edit['unh_d1_drupal_courseSearchBar_filters']);
  }
}

/*
 *
 * SEARCH FORM DEFINITIONS
 *
 */

/**********************************************************
 *
 * FORM: COURSE SEARCH BY TOPIC (What do you want to learn?)
 *
 **********************************************************/

function unh_d1_drupal_courseSearchBar($form, &$form_state) {

  if (!$form_state['submitted']) {
    $phrase = unh_d1_drupal_settings_courseSearchBar_phrase();
    $submit = unh_d1_drupal_settings_courseSearchBar_submit();
    $filters = unh_d1_drupal_settings_courseSearchBar_filters();

    // Can shut these off by checkbox in block config, or if filters taxonomy is empty.
    if ($filters) {
      unh_d1_drupal_get_search_filter_radiobuttons($form, $form_state, 'course_search_filters_format');
    }

    unh_d1_drupal_get_search_subject_checkboxes($form, $form_state, 'course_search_categories');

    $form['#attributes'] = array(
      'enctype' => 'multipart/form-data',
      'class' => array('search-by-topic-form')
    );

    $form['submit']=array(
      '#type'=>'submit',
      '#value'=>t($submit)
    );

    $form['reset'] = array(
      '#type' => 'markup',
      '#markup' => '<input type="reset" class="btn btn-primary form-reset" value="Reset" class="form-submit">',
    );

    $form['#prefix'] = '<div class="search-form-prefix">' . $phrase . '</div>';
  } else {
    $form['submission'] = array(
    '#markup' => unh_d1_drupal_courseSearchBar_getMarkup($form_state)
    );
  }
  return $form;
}


function unh_d1_drupal_courseSearchBar_getMarkup(&$form_state) {

  unh_d1_drupal_get_searchByTopic_results_markup($form_state);

  return $form_state['storage']['html'];
}


function unh_d1_drupal_courseSearchBar_validate($form, &$form_state) {

    //form_set_error('subjects','Please choose a subject.');
}


// search by subject areas
function unh_d1_drupal_courseSearchBar_submit($form, &$form_state) {

  $terms = array();
  $params = array();
  $search_by = 'by-topic';

  $keywords_specified = unh_d1_drupal_keywords_checked($form_state);
  $filters_specified = unh_d1_drupal_filters_checked($form_state);

  if ($filters_specified && !$keywords_specified) {
    $search_by = 'by-filter';
  } elseif ($keywords_specified && !$filters_specified) {
    $search_by = 'by-topic';
  } elseif ($keywords_specified && $filters_specified) {
    $search_by = 'combined';
  } else {
    // Do nothing.  Should not get here.
  }

  $terms = array();
  // Get the tids from the form
  if (!empty($form_state['values']['areas'])) {
    foreach($form_state['values']['areas'] as $area) {
      foreach ($area as $tid => $topic) {
        if (!empty($topic)) {
          $terms[] = $tid;
        }
      }
    }
    if (!empty($terms)) {
      $params['topic'] = implode(',', $terms);
    }
  }

  $filters = array();
  if (!empty($form_state['values']['filters'])) {
    foreach($form_state['values']['filters'] as $filter) {
      if (!empty($filter)) {
        $filters[] = $filter;
      }
    }
    if (!empty($filters)) {
      $params['filters'] = implode(',', $filters);
    }
  }
  $form_state['redirect'] = array(
     'course-search-results/' . $search_by,
      array(
        'query' => $params
      )
    );
  drupal_redirect_form($form_state);
}


/**********************************************************
 *
 * FORM: COURSE SEARCH BY TEXT (Text input with submit button)
 *
 **********************************************************/

function unh_d1_drupal_courseSearchByText($form, &$form_state) {

  if (!$form_state['submitted']) {

    $form['search_text'] = array(
      '#type' => 'textfield',
      '#title' => t(''),
      '#size' => 60,
      '#maxlength' => 128,
      '#required' => TRUE,
      '#attributes' => array(
        'placeholder' => t('-or- type search text here')
      ),
    );

    //$form['#attributes']['enctype'] = 'multipart/form-data';
    $form['#attributes'] = array(
      'enctype' => 'multipart/form-data',
      'class' => array('search-by-text-form')
    );


    $form['submit']=array(
      '#type'=>'submit',
      '#value'=>t('Search by Text'),
      '#attributes' => array(
        'class' => array('btn-highlight', 'search-by-text-btn')
      ),
    );

  } else {
    $form['submission'] = array(
      '#markup' => unh_d1_drupal_courseSearchByText_getMarkup($form_state)
    );
  }

    return $form;
}


function unh_d1_drupal_courseSearchByText_getMarkup(&$form_state) {

  unh_d1_drupal_get_searchByTopic_results_markup($form_state);
  return $form_state['storage']['html'];

}


function unh_d1_drupal_courseSearchByText_validate($form, &$form_state) {

    //form_set_error('subjects','Please choose a subject.');
}


// search by subject areas
function unh_d1_drupal_courseSearchByText_submit($form, &$form_state) {

  $search_by = 'by-text';
  $search_text = $form_state['values']['search_text'];

  $params['search_text'] = $search_text;

  $form_state['redirect'] = array(
     'course-search-results/' . $search_by,
      array(
        'query' => $params
      )
    );

  drupal_redirect_form($form_state);
}


/*
 *
 * GET CHECKBOXES/RADIO BUTTONS FOR SEARCH BAR
 *
 */
function unh_d1_drupal_get_search_subject_checkboxes(&$form, &$form_state, $vocab_machine_name) {

  $vocab = taxonomy_vocabulary_machine_name_load($vocab_machine_name);
  $vid = $vocab->vid;
  $terms = unh_d1_drupal_get_nested_tree($vid);
  $terms_flat = entity_load('taxonomy_term', FALSE, array('vid' => $vocab->vid));

  //uasort($terms, function ($a, $b) { return strnatcasecmp($a->name, $b->name); });

  if (unh_d1_drupal_topicAreasWithChildren($terms)) {
    //$form['areas']['#attributes'] = array('class' => array('my-class-1'));

    $form['areas'] = array(
      '#type' => 'container',
      '#attributes' => array('class' => array('topic-areas')),
      '#tree' => TRUE,

    );

    foreach($terms as $term) {
      if (unh_d1_drupal_term_is_area($term)) {
        $form['areas'][$term->tid] = array(
          '#title' => t($term->name),
          '#type' => 'checkboxes',
        );

        foreach($term->children as $option) {
          $form['areas'][$term->tid]['#options'][$option->tid] = $option->name;
        }
      }
    }

   // $form_state['storage']['vocab'] = $vocab;
   // $form_state['storage']['terms'] = $terms;
    //$form_state['storage']['terms_flat'] = $terms_flat;

    $form_state['storage']['topics']['vocab'] = $vocab;
    $form_state['storage']['topics']['terms'] = $terms;
    $form_state['storage']['topics']['terms_flat'] = $terms_flat;
  }
}

function unh_d1_drupal_get_search_filter_radiobuttons(&$form, &$form_state, $vocab_machine_name) {

  $vocab = taxonomy_vocabulary_machine_name_load($vocab_machine_name);
  $vid = $vocab->vid;
  $terms = entity_load('taxonomy_term', FALSE, array('vid' => $vocab->vid));
  //why am I having to sort these at all?  Why don't we just get them in order of weight (entity_load)?
  uasort($terms, function ($a, $b) { return strnatcasecmp($a->weight, $b->weight); });

  if (!empty($terms)) {

    if (!array_key_exists('filters', $form)) {
      $form['filters'] = array(
        '#type' => 'container',
        '#attributes' => array('class' => array('topic-filters')),
        '#tree' => TRUE,
      );
    }

    $form['filters'][$vid] = array(
      '#type' => 'radios',
      '#title' => t(''),
      '#description' => t(''),
      '#tree' => TRUE,
      '#attributes' => array('class' => array('topic-filters', $vocab_machine_name))
    );

    foreach($terms as $term) {
      $form['filters'][$vid]['#options'][$term->tid] = $term->name;
    }

    // Filters for course format options (bootcamp/workshop/conference)
    $form_state['storage']['filters']['courseFormat']['vocab'] = $vocab;
    $form_state['storage']['filters']['courseFormat']['terms'] = $terms;
  }

  // Perhaps a future set of radio buttons for delivery options (online/onCampus)
  //$form_state['storage']['filters']['courseDelivery']['vocab'] = $vocab;
  //$form_state['storage']['filters']['courseDelivery']['terms'] = $terms;

}

function unh_d1_drupal_get_searchBarBlock_markup () {

  $form = drupal_get_form('unh_d1_drupal_courseSearchByText');
  $form1 = drupal_get_form('unh_d1_drupal_courseSearchBar');
  $label = unh_d1_drupal_settings_courseSearchBar_label();
  $tab = unh_d1_drupal_settings_courseSearchBar_tab();
  $output =  '
<div class="search-bar">
  <div class="search-bar-header">
    <div class="search-hdr left">' . (!empty($label) ? '
      <h2>' . $label . '</h2>' : '') . '
      <button type="button" class="btn btn-highlight choose-topics-btn collapsed" data-toggle="collapse" data-target="#demo">' . $tab . '
      <i class="fa fa-plus"></i>
      <i class="fa fa-minus"></i></button>
    </div>
  <div class="search-hdr right">
' . render($form) . '
    </div>
  </div>
  <div id="demo" class="collapse search-bar-body">
' . render($form1) . '
  </div>
</div>';
  return $output;
}


// DO SUBMIT ACTION - SEARCH BY TOPIC
function unh_d1_drupal_do_searchByTopic_submit_action($form, &$form_state) {
    //in case we don't get any results: empty results array
    $form_state['storage']['results'] = array();
    $form_state['storage']['search-type'] = 'by-topic';

    $keywords_specified = unh_d1_drupal_keywords_checked($form_state);
    $filters_specified = unh_d1_drupal_filters_checked($form_state);

    if ($filters_specified && !$keywords_specified) {
      unh_d1_drupal_search_by_filter($form_state, 'full');
    } elseif ($keywords_specified && !$filters_specified) {
      unh_d1_drupal_search_by_topic($form_state, 'full');
    } elseif ($keywords_specified && $filters_specified) {
      unh_d1_drupal_search_combined_filter_topic($form_state);
    } else {
      // Do nothing.  Should not get here.
    }

    $_SESSION['form_state'] = $form_state;
    $form_state['redirect'] = 'course-search-results';

}

//
// UTILITIES
//

//UTIL: Returns the 'search again' button
function unh_d1_drupal_get_search_again_button($class = '') {
   // return '<div class="search-again-button' . (!empty($class) ? ' ' . $class : '') . '" ><a class="btn btn-primary" href="' . base_path() . 'course-search">Search Again</a></div>';
   return '<div class="search-again-button' . (!empty($class) ? ' ' . $class : '') . '" ><a class="btn btn-primary" href="' . base_path() . 'course-search">Search Again</a></div>';
}

//UTIL: Returns the 'back to top' button.  Used in search results.  Has jquery.
function unh_d1_drupal_get_backToTop_button($name) {
  //return '<div class="back-to-top-button" ><a class="btn btn-primary" href="#' . $name . '">Back To Top</a></div>';
  //return '<div id="back-to-top" class="back-to-top" ><a class="btn btn-primary" href="#">Back To Top</a></div>';
  return '<a id="back-to-top" href="#" class="btn btn-primary btn-lg back-to-top" role="button" title="" data-toggle="tooltip" data-placement="left" data-original-title="Click to return on the top page" style="display: none;"><span class="glyphicon glyphicon-chevron-up"></span></a>';
}


//UTIL: returns the 'no courses found' message.
function unh_d1_drupal_get_search_no_results_text() {
  return '<p class="search-results" style="font-size: 150%;">No courses found for selected categories.</p>' . PHP_EOL;
}


//UTIL: returns prefix text for search results.
function unh_d1_drupal_get_search_results_prefix_text() {
  return '<p class="search-results" style="font-size: 150%;">Courses in these categories are:</p>';
}

function unh_d1_drupal_get_drupal_course_alias($courseCode = NULL) {
  return (unh_d1_drupal_get_drupal_course_alias_D1($courseCode));
}

//UTILS: Given a courseCode, returns the drupal alias (path.
function unh_d1_drupal_get_drupal_course_alias_D1($courseCode) {

  $alias = '';
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'Course')
    ->fieldCondition('field_course_code', 'value', $courseCode);

  $result = $query->execute();
  if (empty($result)) {
    $alias = '';
  } else {
    $last_node = end($result['node']);
    $nid = $last_node->nid;

    $alias = base_path() . drupal_get_path_alias('node/' . $nid);
  }

  return $alias;
}


function unh_d1_drupal_get_drupal_course_alias_other($nid = NULL) {
  if (empty($nid) ) {
    $alias = '';
  } else {
    $node = node_load($nid);

    if (!empty($node)) {
      // THIS IS AN ENROLLMENT LINK!!
      //if (!empty($node->field_course_enrollment_link)) {
      //  $alias = $node->field_course_enrollment_link['und'][0]['url'];
      //} else {
        $alias = base_path() . drupal_get_path_alias('node/' . $nid);
      //}
    }
  }

  return $alias;
}

//UTILS: SEARCH BAR

//UTIL: Given a form with values, returns TRUE if keywords have been checked, otherwise returns FALSE.
function unh_d1_drupal_keywords_checked($form_state) {
  foreach($form_state['values']['areas'] as $topic_list) {
    foreach($topic_list as $topic) {
      if (!empty($topic)) {
        return TRUE;
      }
    }
  }
  return FALSE;
}

//UTIL: Given a form with values, returns TRUE if filters have been checked, otherwise returns FALSE.
function unh_d1_drupal_filters_checked($form_state) {
  foreach($form_state['values']['filters'] as $filter) {
    if (!empty($filter)) {
      return TRUE;
    }
  }
  return FALSE;
}


//SEARCH BAR UTIL: Given a form with values, does the specified search.
function unh_d1_drupal_search_by_filter(&$form_state, $informationLevel = 'full', $exclude_flag = UNH_D1_DRUPAL_EXCLUDE_NONNODE) {
  $filter_type = 'courseFormat';

  list($keyword, $title, $value) = unh_d1_drupal_get_filter_attrs($form_state, 'courseFormat');

  $results = unh_d1_client_searchCourse_keyword($keyword, unh_d1_drupal_settings_program_area(), 'full');

  if (!empty($results)) {

    $courseProfiles = $results;
    $results['courseProfile'] = array();

    foreach($courseProfiles as $key => $course) {
      // Get the URL from drupal based on the course code.
      $url = unh_d1_drupal_get_drupal_course_alias($course['name']);
      if (!(empty($url) && ($exclude_flag === UNH_D1_DRUPAL_EXCLUDE_NONNODE))) {
        $course['courseURL'] = $url;
        $results['courseProfile'][] = $course;
      }
    }

    if ($results) {
      // Sort the courses within a by title.
      uasort($result['courseProfile'], function ($a, $b) { return strnatcasecmp($a['name'], $b['name']); });
    }

    $form_state['storage']['results']['filter'][$filter_type]['filter_title'] = $title;
    $form_state['storage']['results']['filter'][$filter_type]['courseProfiles'] = $result['courseProfile'];
    // What kind of search did we do? (affects result format)
  }

  $form_state['storage']['search-type'] = 'by-filter';

}


//SEARCH BAR UTIL: Given a form with values, does the specified search.
function unh_d1_drupal_search_by_topic(&$form_state, $informationLevel = 'full', $exclude_flag = UNH_D1_DRUPAL_EXCLUDE_NONNODE) {
  // For each area (set of topics).
  foreach ($form_state['values']['areas'] as $area_tid => $topic_tids) {
    // For each topic within an area.
    foreach ($topic_tids as $value) {
      if (!empty($value)) {
        $keyword = $form_state['storage']['topics']['terms_flat'][$value]->field_keyword['und'][0]['value'];
        $topic = $form_state['storage']['topics']['terms_flat'][$value]->name;
        $area_title = $form_state['storage']['topics']['terms_flat'][$area_tid]->name;

        $results = unh_d1_client_searchCourse_keyword($keyword, unh_d1_drupal_settings_program_area(), 'full');

        if (!empty($results)) {
          // Sort the courses within a topic by course title.
          uasort($results['name'], function ($a, $b) { return strnatcasecmp($a['name'], $b['name']); });

          $courseProfiles = $results;
          $results['courseProfile'] = array();

          foreach($courseProfiles as $key => $course) {
            // Get the URL from drupal based on the course code.
            $url = unh_d1_drupal_get_drupal_course_alias($course['courseNumber']);
            if (!(empty($url) && ($exclude_flag === UNH_D1_DRUPAL_EXCLUDE_NONNODE))) {
              $course['courseURL'] = $url;
              $results['courseProfile'][] = $course;
            }
          }

          $form_state['storage']['results']['area'][$area_tid]['area_title'] = $area_title;
          $form_state['storage']['results']['area'][$area_tid]['area_tid'] = $area_tid;
          $form_state['storage']['results']['area'][$area_tid]['topic'][$value]['topic_title'] = $topic;
          $form_state['storage']['results']['area'][$area_tid]['topic'][$value]['courseProfiles'] = $results['courseProfile'];

        }
      }
    }

    // Sort the topics within an area by topic title (if there are any).
    if (!empty($form_state['storage']['results']['area'][$area_tid]['topic'])) {
      uasort($form_state['storage']['results']['area'][$area_tid]['topic'], function ($a, $b)  { return strnatcasecmp($a['topic_title'], $b['topic_title']); });
    }
  }

  // Sort the areas by area title (if there are any).
  if (!empty($form_state['storage']['results'])) {
    uasort($form_state['storage']['results']['area'], function ($a, $b) { return strnatcasecmp($a['area_title'], $b['area_title']); });
  }
  // What kind of search did we do? (affects result format)

  $form_state['storage']['search-type'] = 'by-topic';

}


//SEARCH BAR UTIL: Given a form with values, does the specified search.
function unh_d1_drupal_search_combined_filter_topic(&$form_state) {

  //Then filter out the results we want.
  unh_d1_drupal_search_by_filter($form_state, 'full');

  if (!empty($form_state['storage']['results'])) {
    // First, do the keyword search.
    unh_d1_drupal_search_by_topic($form_state, 'short');
  }

  foreach($form_state['storage']['results']['area'] as $area_key => &$area) {
    foreach($area['topic'] as $topic_key => &$topic) {
      foreach($topic['courseProfiles'] as $course_key => &$course) {
        if ($full_courseProfile = unh_d1_drupal_course_matches_filter($form_state, $course, 'courseFormat')) {
          $course = $full_courseProfile;
        } else {
          unset($topic['courseProfiles'][$course_key]);
        }
      }
      if (empty($topic['courseProfiles'])) {
        unset($area['topic'][$topic_key]);
      }
    }
    if (empty($area['topic'])) {
      unset($form_state['storage']['results']['area'][$area_key]);
    }
  }
  if (empty($form_state['storage']['results']['area'])) {
    unset($form_state['storage']['results']['area']);
    unset($form_state['storage']['results']['filter']);
  }

  // What kind of search did we do? (affects result format)
  $form_state['storage']['search-type'] = 'combined-topic-filter';
}

function unh_d1_drupal_course_matches_filter(&$form_state, &$course, $filter) {

  foreach($form_state['storage']['results']['filter'][$filter]['courseProfiles'] as $courseProfile) {
    if ($course['courseCode'] == $courseProfile['courseCode']) {
      return $courseProfile;
    }
  }

  return NULL;
}

//SEARCH BAR UTIL: Given a form with values and search results, apply the specified filter to the search results.
function unh_d1_drupal_filter_search_results(&$form_state) {

  list($keyword, $title, $value) = _unh_d1_drupal_get_filter_attrs($form_state, 'courseFormat');

  $results = unh_d1_client_searchCourse_keyword($keyword, unh_d1_drupal_settings_program_area(), 'full');


  // Remove all courses that don't match what is in our filter.
}


// SEARCH BAR UTIL: Get the course format filter keyword from the search.
// Example filter types: courseFormat = bootcamp/workshop/conference, courseDelivery = online/oncampus
function unh_d1_drupal_get_filter_attrs($form_state, $filter_type) {
  $vid = $form_state['storage']['filters'][$filter_type]['vocab']->vid;
  $keyword_tid = $form_state['values']['filters'][$vid];
  $keyword = $form_state['storage']['filters'][$filter_type]['terms'][$keyword_tid]->field_keyword['und'][0]['value'];
  $title = $form_state['storage']['filters'][$filter_type]['terms'][$keyword_tid]->name;
  return array($keyword, $title, $keyword_tid);
}


// UTIL: GET APPLICABLE CERTIFICATES BLOCK
function unh_d1_drupal_get_applicable_certificates_block($course) {
  if (empty($course) || empty($course['applicableCertificates'])) {
    return '';
  }
  // todo
  //$certificates = d1client_utils_get_course_applicableCertificates($course);
  $certificates = array();

  $str = '
<ul class="certificates-block">';
  foreach($certificates as $certificate) {
    $str .= '<li><span style="font-weight: 600;">Applicable Certificate:</span> ' . $certificate['name'] . '  (' . $certificate['code'] . ')</li>';
  }
  $str .= '
</ul>';

  return $str;
}


function unh_d1_drupal_get_filter_title_list($filters) {
  if (empty($filters)) {
    $ret = NULL;
  } else {
    $ret = array();
    foreach ($filters as $filter) {
      $ret[] = $filter['filter_title'];
    }
    if (empty($ret)) {
      $ret = NULL;
    }
  }

  return $ret;
}

function unh_d1_drupal_sort_available_courses_first($courses) {
  $ret = array();

  $available_courses = array();
  $unavailable_courses = array();

  foreach ($courses as $course) {
    if (unh_d1_client_courseIsAvailable($course)) {
      $available_courses[] = $course;
    } else {
      $unavailable_courses[] = $course;
    }
  }

  $ret = array_merge($available_courses, $unavailable_courses);

  return $ret;
}


function unh_d1_drupal_filter_available_courses_only($courses) {
  $ret = array();

  $available_courses = array();
  $unavailable_courses = array();

  foreach ($courses as $course) {
    if (unh_d1_client_courseIsAvailable($course)) {
      $available_courses[] = $course;
    } else {
      $unavailable_courses[] = $course;
    }
  }

  $ret = $available_courses;

  return $ret;
}

/*
 *
 * GET MARKUP FOR SEARCH BAR SEARCH RESULTS (DIFFERENT TYPES: by-topic, by-text, by-filter, combined-topic-filter)
 *
 */
 
 function unh_d1_drupal_get_search_results_markup(&$form_state) {

  if ($form_state['storage']['search-type'] == 'by-topic') {
    unh_d1_drupal_get_searchByTopic_results_markup($form_state);
  } elseif ($form_state['storage']['search-type'] == 'by-text') {
    unh_d1_drupal_get_searchByText_results_markup($form_state);
  } elseif ($form_state['storage']['search-type'] == 'by-filter') {
    unh_d1_drupal_get_searchByFilter_results_markup($form_state);
  } elseif ($form_state['storage']['search-type'] == 'combined-topic-filter') {
    unh_d1_drupal_get_searchByTopic_results_markup($form_state, TRUE);
  } else {
    // Should not get here!
  }

  return $form_state['storage']['html'];
}

// UTILS - SEARCH RESULTS from search by topic (upper right search form radio buttons)
function unh_d1_drupal_get_searchByTopic_results_markup(&$form_state, $filtered = FALSE) {
  if (empty($form_state["storage"]["results"])) {
    $form_state['storage']['html'] = unh_d1_drupal_get_search_no_results_text() . unh_d1_drupal_get_search_again_button() . PHP_EOL;
    return $form_state['storage']['html'];
  }

  $filters = NULL;
  if ($filtered) {
    $filter_titles = unh_d1_drupal_get_filter_title_list($form_state['storage']['filters']);
  }

  $str = '<div name="search-results" class="search-results">';
  foreach ($form_state["storage"]["results"]["area"] as $area) {

    $str .= '
<div class="search-area">
  <div class="search-area-header h2">' . $area['area_title'] . (($filtered && $filter_titles) ? ' (' . implode(',', $filter_titles) . ')' : '') . '</div>';
    foreach ($area['topic'] as $topic) {

      $str .= '
    <div class="search-topic">
      <div class="search-topic-header h3">' . $topic['topic_title'] . '</div>
      <div class="search-topic-body">';

      $str .= unh_d1_drupal_get_courseListBlock_markup($topic['courseProfiles']);

      $str .= '
      </div>
    </div>';

    }

    $str .= '
  </div>';
  }
  $str .= '
</div>';

$str = unh_d1_drupal_get_search_again_button('top-of-page') . $str .  unh_d1_drupal_get_backToTop_button('search-results');
//$str = _d1pdt_get_search_again_button('top-of-page') . $str;

  $form_state['storage']['html'] = $str;
  return $form_state['storage']['html'];

}


// UTILS - SEARCH RESULTS from search by filter (upper right search form radio buttons)
function unh_d1_drupal_get_searchByFilter_results_markup(&$form_state) {

  if (empty($form_state["storage"]["results"])) {
    $form_state['storage']['html'] = unh_d1_drupal_get_search_no_results_text() . unh_d1_drupal_get_backToTop_button() . PHP_EOL;
    return $form_state['storage']['html'];
  }

  $str = '<div name="search-results" class="search-results">';
  foreach ($form_state["storage"]["results"]["filter"] as $filter) {
    $str .= '
<div class="search-area">
  <div class="search-area-header h2">' . $filter['filter_title'] . '</div>
  <div class="search-area-body">';

    $str .= unh_d1_drupal_get_courseListBlock_markup($filter['courseProfiles']);

    $str .= '
  </div>
</div>';
  }

  $str .= '
</div>';

  $str = unh_d1_drupal_get_search_again_button('top-of-page') . $str .  unh_d1_drupal_get_backToTop_button('search-results');
  //$str = _d1pdt_get_search_again_button('top-of-page') . $str;

  $form_state['storage']['html'] = $str;
  return $form_state['storage']['html'];
}


// UTILS - SEARCH RESULTS from search by text (upper right search form text search box)
function unh_d1_drupal_get_searchByText_results_markup(&$form_state) {

  if (empty($form_state["storage"]["results"])) {
    $form_state['storage']['html'] = unh_d1_drupal_get_search_no_results_text() . unh_d1_drupal_get_search_again_button() . PHP_EOL;
    return $form_state['storage']['html'];
  }
  $str = '<div name="search-results"  class="search-results">';
  foreach ($form_state["storage"]["results"] as $result) {

    $str .= '
<div class="search-area">
  <div class="search-area-header h2">Search Text: ' . $result['topic'] . '</div>';

    $str .= '
  <div class="search-topic">
    <div class="search-topic-body">';
    $str .= unh_d1_drupal_get_courseListBlock_markup($result['courseProfiles']);

    $str .= '
    </div>
  </div>';

    $str .= '
</div>';
  }
  $str .= '
</div>';

$str = unh_d1_drupal_get_search_again_button('top-of-page') . $str .  unh_d1_drupal_get_backToTop_button('search-results');
//$str = _d1pdt_get_search_again_button('top-of-page') . $str;

  $form_state['storage']['html'] = $str;
  return $form_state['storage']['html'];

}

//GET MARKUP FOR SEARCH results course list

function unh_d1_drupal_get_courseListBlock_markup($courses) {

  if (empty($courses)) {
    return '';
  }

  //FILTER: sort courses, available first, unavailable last.
  $courses = unh_d1_drupal_sort_available_courses_first($courses);

  $str = '
<ul class="list__chevron course-list">';

  foreach ($courses as $course) {

    $course_has_drupal_node = TRUE;
    $course_has_certificates = TRUE;

    //FILTER: This controls the listing of applicable certificates in course search results.
    $list_applicable_certificates = FALSE;

    if (!empty(unh_d1_client_getcourseNumber($course))) {
      $course_is_available = unh_d1_client_courseIsAvailable($course);
    } else {
      $course_is_available = unh_d1_drupal_non_d1_course_is_available($course['node']);
    }

    if (empty($course['applicableCertificates'])) {
      $course_has_certificates = FALSE;
    }
    if (empty($course['courseURL'])) {
      $course_has_drupal_node = FALSE;
    }

    $str .= '
  <li class="course-row">';

    if ($course_has_drupal_node) {
      $str .= '
    ' . (!$course_is_available ? '<span class="course-unavailable">(Currently Unavailable - Request More Information)</span> ' : '') . '<a href="' . $course['courseURL']  . '"' . (!$course_is_available ? ' class="course-unavailable"' : '') . '>' . $course['courseTitle'] .'</a>';
    } else {
      $str .= '
      <span class="course-error">' . $course['courseTitle'] . '</span>';
    }

    if ($list_applicable_certificates && $course_has_certificates) {
       $str .= unh_d1_drupal_get_applicable_certificates_block($course);
    }

    $str .= '
  </li>';
  }

  $str .= '
</ul>';

  return $str;
}


//GET MARKUP FOR SEARCH results course list

function unh_d1_drupal_get_simpleCourseListBlock_markup($courses) {

  if (empty($courses)) {
    return '';
  }

  uasort($courses, function ($a, $b) { return strnatcasecmp($a['courseTitle'], $b['courseTitle']); });

  $str = '
<ul class="list__chevron course-list">';

  foreach ($courses as $course) {

    $str .= '
  <li class="course-row">';

    $str .= '<a href="' . $course['courseURL']  . '>' . $course['courseTitle'] . ' (' . $course['courseCode'] .')</a>';

    $str .= '
  </li>';
  }

  $str .= '
</ul>';

  return $str;
}

/*
 * THE HEART OF THE SEARCH.
 * 
 * Determines search type (text, topic, filter, combined).
 * Does the appropriate search based on search type.
 * Then gets the results markup.
 * 
 * ALL FORMS GO THROUGH HERE BY REDIRECT (TO COURSE-SEARCH-RESULTS PAGE).
 * FORM_STATE IS PASSED THROUGH THE SESSION VARIABLE.
 */
 
/**
 * [unh_d1_drupal_courseSearch_results description]
 * @param string $search_by
 *   Search Type
 * @return string
 *   HTML of the Page
 *
 */
function unh_d1_drupal_courseSearch_results($search_by) {

  $html = '';
  $params = drupal_get_query_parameters();

  $form_state['storage']['results'] = array();
  // do we need this anymore?
  $form_state['storage']['search-type'] = $search_by;
  $form_state['storage']['results'] = array();

  switch($search_by) {
    case 'by-topic':
      if ($valid_terms = unh_d1_drupal_search_by_keywords($params['topic'])) {
        $form_state['storage']['results']['area'] = $valid_terms;
      } else {
        $form_state['storage']['results'] = array();
      }

      $html = unh_d1_drupal_get_searchByTopic_results_markup($form_state);
      break;
    case 'by-filter':
      if ($valid_filters = unh_d1_drupal_search_by_filters($params['filters'])) {
        $form_state['storage']['results']['filter'] = $valid_filters;
      } else {
        $form_state['storage']['results'] = array();
      }

      $html = unh_d1_drupal_get_searchByFilter_results_markup($form_state);
      break;
    case 'combined':
      if ($valid_terms = unh_d1_drupal_search_by_keywords($params['topic'])) {
        if ($valid_filters = unh_d1_drupal_search_by_filters($params['filters'])) {
          if ($filtered_terms = unh_d1_drupal_filter_op($valid_terms, $valid_filters, 'include')) {
            $form_state['storage']['results']['area'] = $filtered_terms;
          } else {
            $form_state['storage']['results'] = array();
          }
        }
        $form_state['storage']['filters'] = $valid_filters;
      } else {
        $form_state['storage']['results'] = array();
      }
      $html = unh_d1_drupal_get_searchByTopic_results_markup($form_state, TRUE);
      break;
    case 'by-text';
      $search_text = $params['search_text'];
      list($total, $results) = unh_d1_drupal_search_by_text($params['search_text']);
      //if ($results = _d1pdt_search_by_text($params['search_text'])) {
      if ($total > 0) {
        $form_state['storage']['results'] = array(array('topic' => $params['search_text'], 'courseProfiles' => $results));
      }

    // The unfortunate attempt at using db_select instead of EntityFieldQuery
    // because of entityFieldQuery's fatal flaw.
    // Db_select did not work either because I DON'T HAVE ACCESS???
    //$query = db_select('node', 'n');
    //$query->condition('n.type', 'course', '=');
    //  ->fields('n', array('nid', 'title'));
    //$query->condition('n.type', 'course', '=')
    //  ->fields('n', array('nid', 'title'));
    //$result = $query->execute();
/*
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'course')
      ->propertyCondition('status', NODE_PUBLISHED)
      ->propertyCondition('title', $search_text, 'CONTAINS');
      //->fieldCondition('field_course_code', 'value', 'NULL', '=');
    $result = $query->execute();
  */

      $html = unh_d1_drupal_get_searchByText_results_markup($form_state);
      break;
    default:
      return MENU_NOT_FOUND;

  }
  // if (empty($output)) {
  //   $output = _d1pdt_get_search_no_results_text() . _d1pdt_get_search_again_button() . PHP_EOL;
  // }

  return $html;
}

/*******************************************************************************
 *
 * Search by text functions - searches all course types.
 *
 * Course Types:
 *    - DestinyOne (D1)
 *    - Other: Eventbrite, Ed2Go, etc
 *
 ******************************************************************************/

function unh_d1_drupal_search_by_text($search_text, $exclude_flag = UNH_D1_DRUPAL_EXCLUDE_ORPHANS) {

  $ret = array(0, array());

  $results1 = unh_d1_drupal_search_by_text_D1($search_text, $exclude_flag);
  $results2 = unh_d1_drupal_search_by_text_other($search_text);
  $total = $results1[0] + $results2[0];
  $results3 = array_merge($results1[1], $results2[1]);

  uasort($results3, function ($a, $b) {
    return strnatcasecmp($a['name'], $b['name']); }
  );

  $ret = array($total, $results3);

  return $ret;
}


/**
 *
 * Search by text functions - searches for DestinyOne courses.
 *
 **/

function unh_d1_drupal_search_by_text_D1($search_text, $exclude_flag = UNH_D1_DRUPAL_EXCLUDE_ORPHANS) {
  $keyword = $search_text;
  $total_courses = 0;

  $results = unh_d1_client_searchCourse_keyword($keyword, unh_d1_drupal_settings_program_area());

  // got the resulting courses from the search, now get the urls from drupal
  if (!empty($results)) {
    uasort($results, function ($a, $b) { return strnatcasecmp(unh_d1_client_getcourseName($a), unh_d1_client_getcourseName($b)); });

    $courseProfiles = $results;
    $results = [];

    foreach($courseProfiles as $key => $course) {
      // Get the URL from drupal based on the course code.
      $url = unh_d1_drupal_get_drupal_course_alias_D1(unh_d1_client_getcourseNumber($course));
      $title = unh_d1_client_getcourseName($course);
      if ($exclude_flag === UNH_D1_DRUPAL_EXCLUDE_ORPHANS) {
        if (!empty($url)) {
          $course['courseURL'] = $url;
          $course['courseTitle'] = $title;
          $results[] = $course;
        }
      } elseif ($exclude_flag === UNH_D1_DRUPAL_EXCLUDE_NON_ORPHANS) {
        if (empty($url)) {
          $course['courseURL'] = $url;
          $course['courseTitle'] = $title;
          $results[] = $course;
        }
      } else { // UNH_D1_DRUPAL_EXCLUDE_NONE
        $course['courseURL'] = $url;
        $course['courseTitle'] = $title;
        $results[] = $course;
      }
    }
  }

  return(array(count($results), $results));
}


/**
 *
 * Search by text functions - searches for other courses (non-d1).
 *
 * Question: Which fields are we going to search? (Title and overview?)
 *
 **/

function unh_d1_drupal_search_by_text_other($search_text) {
  $ret = array();

  // In this case, EntityFieldQuery has another nasty, fatal flaw.
  // This is 'AND'.  There is no 'OR'.  We need a workaround (since we can't
  // use db_select.

  // Get all entities with a non-null course node.
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'course')
    ->propertyCondition('status', NODE_PUBLISHED)
    ->propertyCondition('title', $search_text, 'CONTAINS');

  $result1 = $query->execute();

  // Get all entities with a non-null course node.
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'course')
    ->propertyCondition('status', NODE_PUBLISHED)
    ->fieldCondition('field_overview', 'value', $search_text, 'CONTAINS');

  $result2 = $query->execute();

  $courseProfiles = array();
  $first_result = TRUE;
  foreach (array($result1, $result2) as $result) {
    if (!empty($result)) {
      foreach ($result['node'] as $result) {
        $node = node_load($result->nid);
        if (($first_result && empty($node->field_course_code)) ||
            (!$first_result && empty($node->field_course_code) && (array_search($node->title, array_column($courseProfiles->courseTitle)) === FALSE))) {
          $courseProfile = array(
            'courseCode' => '',
            'courseTitle' => $node->title,
            //'rollUpAvailabilityStatus' => (_d1pdt_course_is_available($node) ? D1PDT_ROLLUP_AVAILABILITY_STATUS_AVAIL : D1PDT_ROLLUP_AVAILABILITY_STATUS_UNAVAIL),
            'rollUpAvailabilityStatus' => (
              unh_d1_drupal_non_d1_course_is_available($node) ?
                array('message' => 'Available', 'label' => 'available') :
                array('message' => 'Not Currently Available', 'label' => 'not_yet_available')),
            'courseURL' => unh_d1_drupal_get_drupal_course_alias_other($result->nid),
            'node' => $node,
          );
          $courseProfiles[] = $courseProfile;
        }
      }
    }
    $first_result = FALSE;
  }
  $ret = array(count($courseProfiles), $courseProfiles);

  return $ret;
}

/*******************************************************************************
 *
 * Search by keyword functions - searches all course types.
 *
 * Course Types:
 *    - DestinyOne (D1)
 *    - Other: Eventbrite, Ed2Go, etc
 *
 ******************************************************************************/

function unh_d1_drupal_search_by_keywords($params, $exclude_flag = UNH_D1_DRUPAL_EXCLUDE_ORPHANS) {
  if (empty($params)) {
    $ret = null;
  } else {
    $terms = explode(',', $params);
    $valid_terms = array();

    foreach ($terms as $tid) {
      if ($term_obj = taxonomy_term_load($tid)) {
        $parent = taxonomy_get_parents($tid);
        // TO DO do this better. Check that exists and be smart about it.
        $parent = array_shift($parent);
        if (empty($valid_terms[$parent->tid])) {
          $valid_terms[$parent->tid] = array(
            'area_title' => $parent->name,
            'area_tid' => $parent->tid,
            'topic' => array(),
          );
        }

        $valid_terms[$parent->tid]['topic'][$tid] = array(
          'topic_title' => $term_obj->name,
          'courseProfiles' => unh_d1_drupal_search_by_keyword_d1($term_obj, $exclude_flag),
        );
        $results1 = $valid_terms[$parent->tid]['topic'][$tid]['courseProfiles'];
        $results2 = unh_d1_drupal_search_by_keyword_other($tid);
        $results3 = array_merge($results1, $results2);
        uasort($results3, function ($a, $b) { return strnatcasecmp($a['courseTitle'], $b['courseTitle']); });

        $valid_terms[$parent->tid]['topic'][$tid]['courseProfiles'] = $results3;
      }
    }

    $valid_terms = unh_d1_drupal_remove_empties($valid_terms);

    if (empty($valid_terms)) {
      $ret = null;
    } else {
      $ret = $valid_terms;
    }
  }

  return $ret;
}


/**
 *
 * Search by keyword functions - searches for DestinyOne courses.
 *
 **/

function unh_d1_drupal_search_by_keyword_d1($term, $exclude_flag = UNH_D1_DRUPAL_EXCLUDE_ORPHANS) {

  $ret = array();

  if (!empty($term)) {
    if (is_numeric($term)) {
      $term = taxonomy_term_load($term);
    }
    
    $wrap = entity_metadata_wrapper('taxonomy_term', $term);
    $keyword = $wrap->field_keyword->value();
    
    $results = unh_d1_client_searchCourse_keyword($keyword, unh_d1_drupal_settings_program_area());
    
    if (!empty($results)) {
      // Sort the courses within a topic by course title.
      uasort($results, function ($a, $b) { return strnatcasecmp(unh_d1_client_getcourseName($a), unh_d1_client_getcourseName($b)); });

      $courseProfiles = $results;
      $results = array();

      foreach($courseProfiles as $key => $course) {
        // Get the URL from drupal based on the course code.
        $url = unh_d1_drupal_get_drupal_course_alias_D1(unh_d1_client_getcourseNumber($course));
        $title = unh_d1_client_getcourseName($course);
        if ($exclude_flag === UNH_D1_DRUPAL_EXCLUDE_ORPHANS) {
          if (!empty($url)) {
            $course['courseURL'] = $url;
            $course['courseTitle'] = $title;
            $result['courseProfile'][] = $course;
          }
        } elseif ($exclude_flag === UNH_D1_DRUPAL_EXCLUDE_NON_ORPHANS) {
          if (empty($url)) {
            $course['courseURL'] = $url;
            $course['courseTitle'] = $title;
            $result['courseProfile'][] = $course;
          }
        } else { // UNH_D1_DRUPAL_EXCLUDE_NONE
          $course['courseURL'] = $url;
          $course['courseTitle'] = $title;
          $result['courseProfile'][] = $course;
        }
      }
    }
    $ret =  $result['courseProfile'] ;
  }

  return $ret;
}


/**
 *
 * Search by keyword functions - searches for other courses (non-d1).
 *
 **/

function unh_d1_drupal_search_by_keyword_other($tid) {
  $ret = array();

  // Unfortunately EntityFieldQuery has a nasty, fatal flaw.  It cannot use ISNULL.
  // The field we are looking at, we want it to be ISNULL.  So we must use this
  // 2 query kludge to work around that flaw.  Otherwise EntityFieldQuery
  // might have been a really nice tool.
  //
  // The hook_query_TAG_alter workaround does not seem to work.
  //
  // And, for some reason I cannot seem to use db_select.
  // That would have been the other alternative.

  // To Do: if all entities with a non-null course node = array() look in all entities!!

  // Get all entities with a non-null course node.
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'course')
    ->propertyCondition('status', NODE_PUBLISHED)
    ->fieldCondition('field_course_code', 'value', 'NULL', '!=');

  $result = $query->execute();

  $result2 = array();
  if (is_array(@$result['node'])) {
    //Now get all the other entities, that aren't in the list you just retrieved
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'course')
      ->propertyCondition('status', NODE_PUBLISHED)
      ->entityCondition('entity_id', array_keys($result['node']), 'NOT IN')
      ->fieldCondition('field_keywords', 'tid', array($tid));
    $result2 = $query->execute();
  }

  $courseProfiles = array();
  if (!empty($result2)) {
    foreach ($result2['node'] as $result) {
      $node = node_load($result->nid);
      $courseProfile = array(
        'courseCode' => '',
        'courseTitle' => $node->title,
        //'rollUpAvailabilityStatus' => (_d1pdt_course_is_available($node) ? D1PDT_ROLLUP_AVAILABILITY_STATUS_AVAIL : D1PDT_ROLLUP_AVAILABILITY_STATUS_UNAVAIL),
        'rollUpAvailabilityStatus' => (
          unh_d1_drupal_non_d1_course_is_available($node)  ?
            array('message' => 'Available', 'label' => 'available') :
            array('message' => 'Not Currently Available', 'label' => 'not_yet_available')),
        'courseURL' => _unh_d1_drupal_get_drupal_course_alias_other($result->nid),
        'node' => $node,
      );
      $courseProfiles[] = $courseProfile;
    }
  }
  $ret = $courseProfiles;

  return $ret;
}

/*******************************************************************************
 *
 * Search by filter functions - searches all course types.
 *
 * This is very similar to the unh_d1_drupal_search_by_keyword_function.
 *
 * Course Types:
 *    - DestinyOne (D1)
 *    - Other: Eventbrite, Ed2Go, etc
 *
 ******************************************************************************/


function unh_d1_drupal_search_by_filters($params, $exclude_flag = UNH_D1_DRUPAL_EXCLUDE_ORPHANS) {
  if (empty($params)) {
    $ret = null;
  } else {
    $terms = explode(',', $params);
    $valid_terms = array();

    foreach ($terms as $tid) {
      if ($term_obj = taxonomy_term_load($tid)) {
        $valid_terms[$tid] = array(
          'filter_title' => $term_obj->name,
          // In d1, these are added the same as keywords.
          'courseProfiles' => unh_d1_drupal_search_by_keyword_d1($term_obj, $exclude_flag),
        );
        $results1 = $valid_terms[$tid]['courseProfiles'];

        $results2 = unh_d1_drupal_search_by_filter_other($tid);

        $results3 = array_merge($results1, $results2);

        uasort($results3, function ($a, $b) { return strnatcasecmp($a['courseTitle'], $b['courseTitle']); });

        $valid_terms[$tid]['courseProfiles'] = $results3;
      }
    }

    $valid_terms = unh_d1_drupal_remove_empties($valid_terms);

    if (empty($valid_terms)) {
      $ret = null;
    } else {
      $ret = $valid_terms;
    }
  }
  return $ret;
}

/**
 *
 * Search by filter functions - searches for other courses (non-d1).
 *
 **/

function unh_d1_drupal_search_by_filter_other($tid) {
  $ret = array();

  // Unfortunately EntityFieldQuery has a nasty, fatal flaw.  It cannot use ISNULL.
  // The field we are looking at, we want it to be ISNULL.  So we must use this
  // 2 query kludge to work around that flaw.  Otherwise EntityFieldQuery
  // might have been a really nice tool.
  //
  // The hook_query_TAG_alter workaround does not seem to work.
  //
  // And, for some reason I cannot seem to use db_select.
  // That would have been the other alternative.

  // To Do: if all entities with a non-null course node = array() look in all entities!!

  // Get all entities with a non-null course node.
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'course')
    ->propertyCondition('status', NODE_PUBLISHED)
    ->fieldCondition('field_course_code', 'value', 'NULL', '!=');

  $result = $query->execute();

  $result2 = array();
  if (is_array(@$result['node'])) {
    //Now get all the other entities, that aren't in the list you just retrieved
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'course')
      ->propertyCondition('status', NODE_PUBLISHED)
      ->entityCondition('entity_id', array_keys($result['node']), 'NOT IN')
      ->fieldCondition('field_filters', 'tid', array($tid));
    $result2 = $query->execute();
  }

  $courseProfiles = array();
  if (!empty($result2)) {
    foreach ($result2['node'] as $result) {
      $node = node_load($result->nid);
      $courseProfile = array(
        'courseCode' => '',
        'courseTitle' => $node->title,
        //'rollUpAvailabilityStatus' => array( 'message' => 'Available', 'label' => 'available'),
        'rollUpAvailabilityStatus' => (
          unh_d1_drupal_course_is_available($node) ?
            array('message' => 'Available', 'label' => 'available') :
            array('message' => 'Not Currently Available', 'label' => 'not_yet_available')),
        //'courseURL' => '/' . drupal_get_path_alias('node/' . $node->nid),
        'courseURL' => unh_d1_drupal_get_drupal_course_alias_other($result->nid),
        'node' => $node,
      );
      $courseProfiles[] = $courseProfile;
    }
  }
  $ret = $courseProfiles;

  return $ret;
}

// UTILITIES

/**
 *
 * Given a generic course structure, determines its type then finds its title/name
 *
 **/

function unh_d1_drupal_get_courseName($course = NULL) {
  $ret = '';
  
  if (!empty($course)) {
    if (!empty(unh_d1_client_getcourseNumber($course))) {
      $ret = unh_d1_client_getcourseName($course);
    }
  } else {
    $ret = $course['courseTitle'];
  }

  return $ret;
}


/**
 *
 * Given a list of terms containing course search results, remove any terms with no courses.
 *
 **/

// Remove all topics and areas with no courses (for filters and terms)
function unh_d1_drupal_remove_empties($terms) {

  if (empty($terms)) {
    return array();
  }
  // Remove empties from terms structure
  $current = current($terms);
  reset($terms);
  if (array_key_exists('topic', $current)) {
    //Looking at an array of terms
    foreach($terms as $area_key => &$area) {
      foreach ($area['topic'] as $topic_key => &$topic) {
        if (empty($topic['courseProfiles'])) {
          // No courses in topic, remove the topic
          unset($area['topic'][$topic_key]);
        }
      }
      if (empty($area['topic'])){
        unset($terms[$area_key]);
      }
    }
  } elseif (array_key_exists('filter_title', $current))  {
    //Looking at an array of filters
    foreach($terms as $filter_key => &$filter) {
      if (empty($filter['courseProfiles'])) {
        // No courses in filter, remove the filter
        unset($filters[$filter_key]);
      }
    }
  }
  if (empty($terms)) {
    $ret = NULL;
  } else {
    $ret = $terms;
  }
  return $ret;
}


function unh_d1_drupal_filter_op($terms, $filters, $op) {
  foreach($terms as &$area) {
    foreach($area['topic'] as &$topic) {
      foreach($topic['courseProfiles'] as $key=>$course) {
        if ($op == 'include') {
          if (!unh_d1_drupal_filter_match($course, $filters)) {
            unset($topic['courseProfiles'][$key]);
          }
          else {
            // Leave it!
          }
        } elseif ($op == 'exclude')  {
          // No exclude op implemented at this time. Skip for now.
        } else {
          // Error - just skip for now.
        }
      }
    }
  }

  $valid_terms = unh_d1_drupal_remove_empties($terms);

  return $valid_terms;
}


function unh_d1_drupal_filter_match($course, $filters) {
  $match = false;
  foreach($filters as $filter) {
    foreach($filter['courseProfiles'] as $filterBy) {
      if ($course['courseCode'] == $filterBy['courseCode']) {
        $match = true;
        break 2;
      }
    }
  }
  return $match;
}






