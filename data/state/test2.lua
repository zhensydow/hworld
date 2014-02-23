fx_flag = false

function start()
   terminal.newLine( 'Start state test2' )
end

function update( dt )
   --print( 'Update state ' .. dt .. ' test2' )
   if input.isKeyUp( input.K )then
      engine.newState( 'test1' )
   end
   if input.isKeyUp( input.R )then
      fx_flag = not fx_flag
      engine.enableRenderEffects( fx_flag )
   end
   if input.isKeyUp( input.S ) then
      engine.saveWorld( '' )
   end
   if input.isButtonPressed( input.MouseLeft )then
      print( "MOUSED" )
   end
end

function stop()
   terminal.newLine( 'Stop state test2' )
end
