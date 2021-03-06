/*
   Copyright (C) 2013 Samuel Kogler

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef OGRETERRAINMATERIALGENERATOREMBER_H
#define OGRETERRAINMATERIALGENERATOREMBER_H

#include <OgreTerrainMaterialGenerator.h>
#include <sigc++/signal.h>

namespace Ember
{
namespace OgreView
{
class IPageDataProvider;

namespace Terrain
{


/**
 * @brief A simple material generator which doesn't do anythings special.
 * @see EmberTerrainProfile for more information.
 */
class OgreTerrainMaterialGeneratorEmber : public Ogre::TerrainMaterialGenerator
{
public:
	OgreTerrainMaterialGeneratorEmber();

};


/**
 * @brief A material generator profile that always uses the material generated by Ember.
 * Most parameters and settings are ignored.
 */
class EmberTerrainProfile : public Ogre::TerrainMaterialGenerator::Profile
{
public:
    const static std::string ERROR_MATERIAL;

    EmberTerrainProfile(IPageDataProvider& dataProvider, Ogre::TerrainMaterialGenerator* parent);
	virtual ~EmberTerrainProfile();

	/** Return whether this profile supports using a compressed
	        vertex format. This is only possible when using shaders.
	 */
	virtual bool isVertexCompressionSupported() const
	{
		// TODO SK: not supported for now
		return false;
	}
	/** Triggers the generator to request the options that it needs.
	 */
	virtual void requestOptions(Ogre::Terrain* terrain);

	/** Generate a material for the given terrain using the active profile.
	 */
	virtual Ogre::MaterialPtr generate(const Ogre::Terrain* terrain);
	/** Generate a material for the given composite map of the terrain using the active profile.
	 */
	virtual Ogre::MaterialPtr generateForCompositeMap(const Ogre::Terrain* terrain);
	/** Whether to support a light map over the terrain in the shader,
	   if it's present (default true).
	 */
	virtual void setLightmapEnabled(bool enabled)
	{
		// We don't use this.
	}
	/** Get the maximum number of layers supported with the given terrain.
	   @note When you change the options on the terrain, this value can change.
	 */
	virtual Ogre::uint8 getMaxLayers(const Ogre::Terrain* terrain) const
	{
		// We don't use this.
		return 0;
	}


	/** Update parameters for the given terrain.
	 */
	virtual void updateParams(const Ogre::MaterialPtr& mat, const Ogre::Terrain* terrain)
	{
	}
	/** Update parameters for the given terrain composite map using the active profile.
	 */
	virtual void updateParamsForCompositeMap(const Ogre::MaterialPtr& mat, const Ogre::Terrain* terrain)
	{
		// We don't use this.
	}


protected:
	IPageDataProvider& mDataProvider;

	/**
	 * @brief A template material to use whenever an error material is needed.
	 *
	 * Since the terrain system takes care of destroying any materials used in pages we can't use this directly; we need to use a clone.
	 */
	Ogre::MaterialPtr mErrorMaterialTemplate;

	/**
	 * @brief Gets a clone of the supplied material, or creates a clone if none is found.
	 * @param templateMaterial A template material.
	 * @param suffix A suffix used together with the name of the template material.
	 * @return A valid material pointer.
	 */
	Ogre::MaterialPtr getOrCreateMaterialClone(Ogre::MaterialPtr templateMaterial, const std::string& suffix);

};
} /* Terrain */
} /* OgreView */
} /* Ember */

#endif /* end of include guard: OGRETERRAINMATERIALGENERATOREMBER_H */
