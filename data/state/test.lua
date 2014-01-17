dtime = 0
keyS = false

function start()
   terminal.newLine( 'Start state' )

   camera = engine.newEntity( 'simple_cam' )
   engine.setCamera( camera )

   tree = engine.newEntity( 'tree01' )
   tree.transform:setPosition( 0, 1, 2 )

   rock = engine.newEntity( 'rock01' )
   rock.transform:setPosition( 0, 2, 0 )
end

function update( dt )
   dtime = dtime + dt
   --print( 'Update state ' .. dt .. ' and ' .. dtime )
   --tree.transform:setPosition( 0, dtime / 4.0, 0 )
   if dtime > 1 then
      engine.newState( 'test2' )
      dtime = 0
   end

   if keyS then
      if not input.isKeyPressed( input.S ) then
         keyS = false
         engine.saveWorld( '' )
      end
   else
      keyS = input.isKeyPressed( input.S )
   end

end

function stop()
   terminal.newLine( 'Stop state' )
end
