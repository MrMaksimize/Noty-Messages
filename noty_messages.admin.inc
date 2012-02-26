<?php

/**
 * Implements hook_settings().
 * Configuration settings page.
 *
 * @return
 *    Array of the system settings form.
 */
function noty_messages_settings() {
  // Per message configs
  $form['noty_messages_settings'] = array(
    '#type' => 'vertical_tabs',
  );
  $message_types = drupal_map_assoc(array('status', 'warning', 'error'));
  $defaults = array(
    'is_noty' => variable_get('noty_messages_is_noty', FALSE),
    'layout' => variable_get('noty_messages_layout', NOTY_LAYOUT),
    'text_align' => variable_get('noty_messages_text_align', NOTY_TEXT),
    'speed' => variable_get('noty_messages_speed', NOTY_SPEED),
    'timeout' => variable_get('noty_messages_timeout', NOTY_TIMEOUT),
    'closable' => variable_get('noty_messages_closable', NOTY_CLOSABLE),
    'click_close' => variable_get('noty_messages_click_close', NOTY_CLICK_CLOSE),
    'modal' => variable_get('noty_messages_modal', NOTY_MODAL),
    'admin_path' => variable_get('noty_messages_admin_path', NOTY_ON_ADMIN),
  );
  foreach ($message_types as $message_type){
    $settings_key = 'noty_messages_' . $message_type . '_settings';
    $form[$settings_key] = array(
      '#type' => 'fieldset',
      '#title' => t('@type messages', array('@type' => $message_type)),
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
      '#description' => t('Configuration for @type messages.', array('@type' => $message_type)),
      '#group' => 'noty_messages_settings',
    );
    $form[$settings_key]['noty_messages_' . $message_type . '_is_noty'] = array(
      '#type' => 'checkbox',
      '#title' => t('This is a noty message type'),
      '#description' => t('Check to have this message displayed as a noty message'),
      '#default_value' => isset($defaults['is_noty'][$message_type]) ? $defaults['is_noty'][$message_type] : FALSE,
    );
    // layout of messages on the screen
    $form[$settings_key]['noty_messages_' . $message_type . '_layout'] = array(
      '#type' => 'select',
      '#title' => t('Message Layout'),
      '#options' => array(
        'layout_top' => t('Top'),
        'layout_top_center' => t('Top Center'),
        'layout_bottom' => t('Bottom'),
        'layout_center' => t('Center'),
        'layout_top_left' => t('Top Left'),
        'layout_top_right' => t('Top Right'),
      ),
      '#description' => t('Where the messages should appear on the screen'),
      '#default_value' => isset($defaults['layout'][$message_type]) ? $defaults['layout'][$message_type] : NOTY_LAYOUT,
    );
    $form[$settings_key]['noty_messages_' . $message_type . '_text_align'] = array(
      '#type' => 'select',
      '#title' => t('Message Text Alignment'),
      '#options' => array(
        'text_left' => t('Left'),
        'text_right' => t('Right'),
          'text_center' => t('Center'),
        'text_justify' => t('Justify'),
      ),
      '#description' => t('How should the text inside the message be aligned'),
      '#default_value' => isset($defaults['text_align'][$message_type]) ? $defaults['text_align'][$message_type] : NOTY_TEXT,
    );
    $form[$settings_key]['noty_messages_' . $message_type . '_speed'] = array(
      '#type' => 'textfield',
      '#title' => t('Speed'),
      '#field_suffix' => t('ms'),
      '#description' => t('The time in milliseconds for the notice to fade in and fade out'),
      '#default_value' => isset($defaults['speed'][$message_type]) ? $defaults['speed'][$message_type] : NOTY_SPEED
    );
    $form[$settings_key]['noty_messages_' . $message_type . '_timeout'] = array(
      '#type' => 'textfield',
      '#title' => t('Timeout'),
      '#field_suffix' => t('ms'),
      '#description' => t('The time in milliseconds the notice will display for, before fading out.'),
      '#default_value' => isset($defaults['timeout'][$message_type]) ? $defaults['timeout'][$message_type] : NOTY_TIMEOUT,
    );
    $form[$settings_key]['noty_messages_' . $message_type . '_closable'] = array(
      '#type' => 'checkbox',
      '#title' => t('Closable'),
      '#description' => t('Check to enable close button.'),
      '#default_value' => isset($defaults['closable'][$message_type]) ? $defaults['layout'][$message_type] : NOTY_CLOSABLE,
    );
    $form[$settings_key]['noty_messages_' . $message_type . '_click_close'] = array(
      '#type' => 'checkbox',
      '#title' => t('Close on self click'),
      '#description' => t('Can the user dismiss the message by clicking on it'),
      '#default_value' => isset($defaults['click_close'][$message_type]) ? $defaults['click_close'][$message_type] : NOTY_CLICK_CLOSE,
    );
    $form[$settings_key]['noty_messages_' . $message_type . '_modal'] = array(
      '#type' => 'checkbox',
      '#title' => t('Message Modal'),
      '#description' => t('Should the background fade out when message is displayed'),
      '#default_value' => isset($defaults['modal'][$message_type]) ? $defaults['modal'][$message_type] : NOTY_MODAL,
    );
    $form[$settings_key]['noty_messages_' . $message_type . '_admin_path'] = array(
      '#type' => 'checkbox',
      '#title' => t('Disable noty messages on admin paths'),
      '#description' => t('Checking this box will disable noty messages on admin paths,
        as determined by the path_is_admin() function.'),
      '#default_value' => isset($defaults['admin_path'][$message_type]) ? $defaults['admin_path'][$message_type] : NOTY_ON_ADMIN,
    );
    //@todo buttons
    //@todo jquery_ui_easing
  }// foreach
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
    //compile arrays to store in variables
    $message_types = drupal_map_assoc(array('status', 'warning', 'error'));
    $values = array();
    foreach ($message_types as $message_type){
      //don't process if it's not a noty message type
      if ($form_state['values']['noty_messages_' . $message_type . '_is_noty'] == TRUE){
        $values['is_noty'][$message_type] = $form_state['values']['noty_messages_' . $message_type . '_is_noty'];
        $values['layout'][$message_type] = $form_state['values']['noty_messages_' . $message_type . '_layout'];
        $values['text_align'][$message_type] = $form_state['values']['noty_messages_' . $message_type . '_text_align'];
        $values['speed'][$message_type] = $form_state['values']['noty_messages_' . $message_type . '_speed'];
        $values['timeout'][$message_type] = $form_state['values']['noty_messages_' . $message_type . '_timeout'];
        $values['closable'][$message_type] = $form_state['values']['noty_messages_' . $message_type . '_closable'];
        $values['click_close'][$message_type] = $form_state['values']['noty_messages_' . $message_type . '_click_close'];
        $values['modal'][$message_type] = $form_state['values']['noty_messages_' . $message_type . '_modal'];
        $values['admin_path'][$message_type] = $form_state['values']['noty_messages_' . $message_type . '_admin_path'];
      }
    }
    foreach ($values as $key => $value){
      variable_set('noty_messages_' . $key, $value);
    }
    drupal_set_message(t('The configuration has been saved.'));
  }
}