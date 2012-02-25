<?php

/**
 * Implements hook_settings().
 * Configuration settings page.
 *
 * @return
 *    Array of the system settings form.
 */
function noty_messages_settings() {
  $module_path = drupal_get_path('module', 'noty_messages');
  if (!libraries_get_path('noty')){
    $form['noty_messages_code_status'] = array(
      '#type' => 'fieldset',
      '#title' => t('noty Messages settings'),
      '#weight' => -10,
      '#description' => t('Please install noty'),
    );
    return $form;
  }
  $form['noty_messages_code_status'] = array(
    '#type' => 'fieldset',
    '#title' => t('noty Messages settings'),
    '#weight' => -10,
  );
  $form['noty_messages_settings'] = array(
    '#type' => 'fieldset',
    '#title' => 'Noty Messages Plugin Settings',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  // position of messages on the screen
  $form['noty_messages_settings']['noty_messages_position'] = array(
    '#type' => 'select',
    '#title' => t('Position'),
    '#options' => array(
      'pos_top' => t('Top'),
      'pos_top_center' => t('Top Center'),
      'pos_bottom' => t('Bottom'),
      'pos_center' => t('Center'),
      'pos_top_left' => t('Top Left'),
      'pos_top_right' => t('Top Right'),
    ),
    '#description' => t('Where the messages should appear'),
    '#default_value' => variable_get('noty_messages_position', NOTY_POSITION),
  );
  // text alignment on messages
  $form['noty_messages_settings']['noty_messages_text_alignment'] = array(
    '#type' => 'select',
    '#title' => t('Text Alignment'),
    '#options' => array(
      'text_left' => t('Left'),
      'text_right' => t('Right'),
      'text_center' => t('Center'),
      'text_justify' => t('Justify'),
    ),
    '#description' => t('Text alignment'),
    '#default_value' => variable_get('noty_messages_text_alignment', NOTY_TEXT),
  );
  $form['noty_messages_settings']['noty_messages_speed'] = array(
    '#type' => 'textfield',
    '#title' => t('Speed'),
    '#field_suffix' => t('ms'),
    '#description' => t('The time in milliseconds for the notice to fade in.'),
    '#default_value' => variable_get('noty_messages_speed', NOTY_SPEED),
  );
  $form['noty_messages_settings']['noty_messages_timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Timeout'),
    '#field_suffix' => t('ms'),
    '#description' => t('The time in milliseconds the notice will display for, before fading out.'),
    '#default_value' => variable_get('noty_messages_timeout', NOTY_TIMEOUT),
  );
  $form['noty_messages_settings']['noty_messages_closable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Closable'),
    '#description' => t('Check to enable close button.'),
    '#default_value' => variable_get('noty_messages_closable', NOTY_CLOSABLE),
  );
  $form['noty_messages_settings']['noty_messages_click_close'] = array(
    '#type' => 'checkbox',
    '#title' => t('Close on self click'),
    '#description' => t('Click to close'),
    '#default_value' => variable_get('noty_messages_click_to_close', NOTY_CLICK_TO_CLOSE),
  );
  $form['noty_messages_settings']['noty_messages_theme'] = array(
    '#type' => 'select',
    '#title' => t('Theme'),
    '#options' => array(
      'default' => t('Default'), //@todo pull themes
    ),
    '#description' => t('Theme'),
    '#default_value' => variable_get('noty_messages_theme', NOTY_THEME),
  );
  $form['noty_messages_settings']['noty_messages_modal'] = array(
    '#type' => 'checkbox',
    '#title' => t('Modal'),
    '#description' => t('Should the background fade out'),
    '#default_value' => variable_get('noty_messages_modal', NOTY_MODAL),
  );
  $form['noty_messages_settings']['noty_messages_modal_css'] = array(
    '#type' => 'textarea',
    '#title' => t('Modal CSS'),
    '#description' => t('CSS to apply to the modal layer'),
    '#default_value' => variable_get('noty_messages_modal_css', NOTY_MODAL_CSS),
  );

  /*
   @todo:
   Theme pull
   animate open
   animate close?
   easing?
   force? which ones?
   buttons
    type - button class
    text = text
    click - callback on click
   on show
   on close
   clear queue?
  */
  // Visibility settings.
  $form['visibility_title'] = array(
    '#type' => 'item',
    '#title' => t('Visibility settings'),
  );
  $form['visibility'] = array(
    '#type' => 'vertical_tabs',
  );
  //@todo per path visibility
  $form['visibility']['other'] = array(
    '#type' => 'fieldset',
    '#title' => t('Other'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#group' => 'visibility',
    '#weight' => 10,
  );
  $form['visibility']['other']['noty_messages_admin_path'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable noty messages on admin paths'),
    '#description' => t('Checking this box will disable noty messages on admin paths,
      as determined by the path_is_admin() function.'),
    '#default_value' => variable_get('noty_messages_admin_path', NOTY_ON_ADMIN),
  );
  $form['visibility']['types'] = array(
    '#type' => 'fieldset',
    '#title' => t('Message Types'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#group' => 'visibility',
    '#weight' => 10,
  );
  
  $form['visibility']['types']['noty_messages_active_message_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Enable Noty on these message types'),
    '#description' => t('Picking a message type will allow you discern which message types will be noty enabled and which ones will be standard system message'),
    '#options' => drupal_map_assoc(array('status', 'warning', 'error')),
    '#default_value' => variable_get('noty_messages_active_message_types', drupal_map_assoc(array('status', 'warning', 'error'))),
  );
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  return $form;
}

/**
 * Form submission handler for the configuration form.
 *
 * @see noty_messages_settings()
 */
function noty_messages_settings_submit($form, &$form_state) {
  if (!form_get_errors()) {
    variable_set('noty_messages_position', $form_state['values']['noty_messages_position']);
    variable_set('noty_messages_text_alignment', $form_state['values']['noty_messages_text_alignment']);
    variable_set('noty_messages_speed', $form_state['values']['noty_messages_speed']);
    variable_set('noty_messages_timeout', $form_state['values']['noty_messages_timeout']);
    variable_set('noty_messages_closable', $form_state['values']['noty_messages_closable']);
    variable_set('noty_messages_click_close', $form_state['values']['noty_messages_click_close']);
    variable_set('noty_messages_theme', $form_state['values']['noty_messages_theme']);
    variable_set('noty_messages_modal', $form_state['values']['noty_messages_modal']);
    variable_set('noty_messages_modal_css', $form_state['values']['noty_messages_modal_css']);
    variable_set('noty_messages_active_message_types', $form_state['values']['noty_messages_active_message_types']);
    variable_set('noty_messages_admin_path', $form_state['values']['noty_messages_admin_path']);
    drupal_set_message(t('The configuration has been saved.'));
  }
}