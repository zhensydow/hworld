dtime = 0

function start()
   terminal.newLine( 'Start state test' )

   if not (world.terrainFocus() == 0) then
      world.setTerrainFocus( 0 )
   end

   if not engine.hasCamera() then
      camera = engine.newEntity( 'simple_cam' )
      engine.setCamera( camera )
   end

   tree = engine.newEntity( 'tree01' )
   tree.transform:setPosition( 0, 1, 2 )

   rock = engine.newEntity( 'rock01' )
   rock.transform:setPosition( 0, 2, 0 )

   game.setSunDir( 0, -1, -1 );
end

function update( dt )
   dtime = dtime + dt
   --print( 'Update state ' .. dt .. ' and ' .. dtime )
   --tree.transform:setPosition( 0, dtime / 4.0, 0 )

   angle1 = dtime*100
   rot1 = glm.rotate( angle1, 0.0, 1.0, 0.0 )
   axis2 = rot1:mul( glm.vec4( 0, -1, -1, 0.0 ) )

   game.setSunDir( axis2:get(0), axis2:get(1), axis2:get(2) )

   if dtime > 2 then
      engine.newState( 'test2' )
      dtime = 0
   end

   if input.isKeyUp( input.S ) then
      engine.saveWorld( '' )
   end

end

function stop()
   terminal.newLine( 'Stop state test' )
end
