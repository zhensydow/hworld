function start()
   terminal.newLine( 'Start state test0' )

   focus = 0
   if not (world.terrainFocus() == focus) then
      if world.hasChunk( focus ) then
         world.setTerrainFocus( focus )
      end
   end

   if not engine.hasCamera() then
      camera = engine.newEntity( 'simple_cam' )
      engine.setCamera( camera )
   end

   if not world.hasEntity( 0, 1 ) then
      for i = 1,18 do
         tree = engine.newEntity( 'tree01' )
         world.addEntity( i, 1, tree )
         tree = engine.newEntity( 'tree01' )
         world.addEntity( i, 4, tree )
      end
      tree = engine.newEntity( 'tree01' )
      world.addEntity( 1, 3, tree )
      tree:printDebug()
   end

   if not world.hasEntity( 0, 0 ) then
      rock = engine.newEntity( 'rock01' )
      world.addEntity( 0, 0, rock )
   end

   game.setSunDir( 0, -1, -1 );
end

function update( dt )
   engine.newState( 'test2' )
end

function stop()
   terminal.newLine( 'Stop state test0' )
end
