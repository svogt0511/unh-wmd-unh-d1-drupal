<?php
  $output = '';
  $form_state = $variables['form_state'];

  if (empty($form_state["storage"]["results"])) {
    $str = unh_d1_drupal_get_search_no_results_text() . unh_d1_drupal_get_search_again_button() . PHP_EOL;
  } else {
  
    $str = '
<div name="search-results"  class="search-results">';

    foreach ($form_state["storage"]["results"] as $result) {
      $str .= '
  <div class="search-area">
    <div class="search-area-header h2">Search Text: ' . $result['topic'] . '</div>';

      $str .= '
    <div class="search-topic">
      <div class="search-topic-body">';

      $str .= theme('unh_d1_drupal__course_search_results__course_list_block', array('course_profiles' => $result['courseProfiles']));  
        
      // $str .= unh_d1_drupal_get_courseListBlock_markup($result['courseProfiles']);

      $str .= '
      </div>
    </div>';

      $str .= '
  </div>';
    }
    
    $str .= '
</div>';

    $str = unh_d1_drupal_get_search_again_button('top-of-page') . $str .  unh_d1_drupal_get_backToTop_button('search-results');
  }

  $output = $str;
?>

<?=$output?>
