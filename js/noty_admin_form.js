(function($) {
  Drupal.behaviors.noty_messages = {
    attach: function(context) {
      console.log(context);
      // button click
      $('.test-noty-messages').click(function(event){
        event.preventDefault();
        event.stopPropagation();
        // get name
        var name = $(this).attr('name');
        // get current actives
        if (name == 'global' || $('#edit-settings-global-is-noty-' + name).is(':checked')){
          // change settings
          var notySettings = Drupal.settings.notyMessages;
          notySettings.notyType[name] = $('#edit-settings-' + name + '-type :selected').val();
          notySettings.notyLayout[name] = $('#edit-settings-' + name + '-layout :selected').val();
          notySettings.notyTextAlign[name] = $('#edit-settings-' + name + '-text-align :selected').val();
          notySettings.notySpeed[name] = $('#edit-settings-' + name + '-speed').val();
          notySettings.notyTimeout[name] = $('#edit-settings-' + name + '-timeout').val();
          notySettings.notyClosable[name] = $('#edit-settings-' + name + '-closable').is(':checked');
          notySettings.notyClickClose[name] = $('#edit-settings-' + name + '-click-close').is(':checked');
          notySettings.notyModal[name] = $('#edit-settings-' + name + '-modal').is(':checked');
          testMessages = new Array('This is a ' + name + ' message', 'And this is another one!');
          new notyMessages.renderType(name, testMessages, notySettings);
        }
        else{
          alert('This is not a noty message');
        }
        return false;
      });
      /*$('input[id$="use-global"]', context).click(function(event){
        // split up the id to get the message name
        var name = $(this).attr('id').split('-');
        name = name[2];
        if ($(this).is(':checked')){
          console.log(name);
        }
        else{
          console.log('unchecked');
        }
      });*/
    }
  }
})(jQuery);